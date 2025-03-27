// some code of the TLS server

#include <stdio.h>
#include <io.h>
#include <ws2spi.h>
#include <string.h>

#include <signal.h>

#include <ws2tcpip.h>
#include <winsock2.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

int create_socket(int port)
{
    int s;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //s = socket(AF_INET, SOCK_STREAM, 0);
    s = 0;
    if (s < 0) {
        perror("Unable to create socket");
        exit(EXIT_FAILURE);
    }
        
}
int main() {
    print("hi");
}