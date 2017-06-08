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
	SOCKET sock;
	SOCKADDR_IN addr;

	WSAStartup(MAKEWORD(2, 2), &wsa); // init the dll

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
		return 1;

	// Connection to server
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT_NUMBER);
	if (connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		closesocket(sock);
		return 2;
	}

	// Sending ping...
	if (send(sock, "PING", 4, 0) == SOCKET_ERROR)
	{
		closesocket(sock);
		return 3;
	}

	// recieving pong...
	memset(buf, 0, MSG_LEN);
	if (recv(sock, buf, 128, 0) == SOCKET_ERROR)
	{
		closesocket(sock);
		return 4;
	}
	printf("%s\n", buf);

	// Test done, closing socket
	closesocket(sock);

	WSACleanup(); // release the dll

	getchar();

	return 0;
}