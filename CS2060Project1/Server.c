


#include <winsock2.h>
#include <windows.h>
#include <signal.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/crypto.h>

#define OPENSSL_API_COMPAT 0x10100000L
#define OPENSSL_NO_DEPRECATED

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "libcrypto.lib")

#define PORT 4433

int socket_creation()
{
    puts("hi");
    int sock;
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
    {
        perror("cannot create socket - exiting");
        exit(EXIT_FAILURE);
    }

    if (bind(sock, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        perror("cannot bind - exiting");
        exit(EXIT_FAILURE);
    }

    if (listen(sock, 1) < 0)
    {
        perror("cannot listen - exiting");
        exit(EXIT_FAILURE);

    }

    return sock;
}

SSL_CTX* context_creation()
{
    const SSL_METHOD* s_method;
    SSL_CTX* s_ctx;

    s_method = TLS_server_method();
    s_ctx = SSL_CTX_new(s_method);

    if (!s_ctx)
    {
        perror("cannot create SSL context - exiting");
        exit(EXIT_FAILURE);
    }

    if (SSL_CTX_set_min_proto_version(s_ctx, TLS1_2_VERSION) != 1)
    {
        perror("error setting minimum TLS version to 1.2 - exiting");
        exit(EXIT_FAILURE);

    }

    return s_ctx;
}

void context_config(SSL_CTX* ctx)
{
    if (SSL_CTX_use_certificate_file(ctx, "server.crt", SSL_FILETYPE_PEM) <= 0)
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, "server.key", SSL_FILETYPE_PEM) <= 0)
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

}

int main()
{
    int main_sock;
    SSL_CTX* main_ctx;
    WSADATA wsaData;

    printf("OpenSSL version: %s\n", OPENSSL_VERSION_TEXT);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        fprintf(stderr, "WSAStartup failed.\n");
        return 1;
    }

    main_ctx = context_creation();
    context_config(main_ctx);

    main_sock = socket_creation(PORT);

    while(1)
    {
        struct sockaddr_in main_address;
        unsigned int length = sizeof(main_address);
        SSL* main_ssl;
        const char reply[] = "test\n";

        int client = accept(main_sock, (struct sockaddr*)&main_address, &length);

        if (client < 0)
        {
            perror("cannot accept - exiting");
            exit(EXIT_FAILURE);
        }

        main_ssl = SSL_new(main_ctx);
        SSL_set_fd(main_ssl, client);

        if (SSL_accept(main_ssl) <= 0)
        {
            ERR_print_errors_fp(stderr);
        }
        else
        {
            SSL_write(main_ssl, reply, strlen(reply));
        }

        SSL_shutdown(main_ssl);
        SSL_free(main_ssl);
        closesocket(client);
    }

    closesocket(main_sock);
    SSL_CTX_free(main_ctx);
    WSACleanup();

}
