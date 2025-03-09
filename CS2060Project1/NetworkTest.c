// Mason Andersen
// Zachary Donnelly
// project 1
// CS 4220
// https://www.binarytides.com/winsock-socket-programming-tutorial/ 


#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")



int main() {

	// some kinda windows socket stuff 
	WSADATA wsa;
	SOCKET s; 
	struct sockaddr_in server;
	char* message;
	char server_reply[10000];
	int recv_size;

	printf("initializing winsock \n");
	// start up the winsock library 
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("FAILURE. Error code: %d", WSAGetLastError());
		return 1;
	}

	printf("initialized successfully\n");

	// AF_INET being IPv4 protocol, 
	// SOCK_STREAM being connection-oriented TCP protocol
	// 0 is also IP I think
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket. Error code: %d", WSAGetLastError());
	}

	printf("Socket Created. \n");

	// set up server, IP is google.com 
	server.sin_addr.s_addr = inet_addr("172.217.20.206");
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	puts("beginning connection to google.com: ");

	// connect to that server (google) now with the socket previously created
	if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
		puts("connection error");
		return 1;
	}

	puts("Connected successfully");

	// send data 
	message = "GET / HTTP/1.1\r\n\r\n"; // this is an HTTP command to fetch the main page of the website
	if (send(s, message, strlen(message), 0) < 0) {
		puts("Send failed");
		return 1;
	}

	puts("Data sent successfully");

	// get a reply from Google
	recv_size = recv(s, server_reply, sizeof(server_reply) - 1, 0);
	if (recv_size == SOCKET_ERROR)
	{
		puts("Recieve Failed");
	}


	// attempted to fix out out bounds error - truncating if too large before null terminating
	if (recv_size < sizeof(server_reply))
	{
		server_reply[recv_size] = '\0';
	}
	else
	{
		server_reply[sizeof(server_reply) - 1] = '\0';
	}

	puts("Reply received");

	// so somewhere this gets really jacked up I do think it's because of the size of recv_size
	// but increasing it doesnt seeem to fix it so I'll check on that later
	// Either way I do think this sends and recieves from a server so thats a start

	// print that jawn 
	printf("%s\n", server_reply);

	// clean up
	closesocket(s);
	WSACleanup();

	return 0;
}