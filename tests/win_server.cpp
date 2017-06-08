#include <WinSock2.h>
#include <windows.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define PORT_NUMBER 42000
#define MSG_LEN 128

int main()
{
	char buf[MSG_LEN];
	WSADATA wsa;
	SOCKET serv_sock;
	SOCKET cli_sock;
	SOCKADDR_IN serv;
	SOCKADDR_IN cli;
	socklen_t socklen = sizeof(SOCKADDR_IN);

	WSAStartup(MAKEWORD(2, 2), &wsa);

	serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serv_sock == INVALID_SOCKET)
		return 1;

	memset(&serv, 0, socklen);
	memset(&cli, 0, socklen);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(PORT_NUMBER);
	if (bind(serv_sock, (SOCKADDR*)&serv, socklen) == SOCKET_ERROR)
	{
		closesocket(serv_sock);
		return 2;
	}
	
	if (listen(serv_sock, 1) == SOCKET_ERROR)
	{
		closesocket(serv_sock);
		return 3;
	}

	cli_sock = accept(serv_sock, (SOCKADDR*)&cli, &socklen);
	if (cli_sock == INVALID_SOCKET)
	{
		closesocket(serv_sock);
		return 4;
	}

	memset(buf, 0, MSG_LEN);
	if (recv(cli_sock, buf, MSG_LEN, 0) == SOCKET_ERROR)
	{
		closesocket(serv_sock);
		closesocket(cli_sock);
		return 5;
	}
	printf("%s\n", buf);

	send(cli_sock, "PONG", 4, 0);

	closesocket(serv_sock);
	closesocket(cli_sock);

	WSACleanup();
	
	getchar();

	return 0;
}