/*
** server.cpp for CPP_Simple_Networking_Library in /home/soszyn_h/Documents/Projects/CPP_Simple_Networking_Library/tests/server.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Thu Jun 08 11:16:55 2017 Hugo SOSZYNSKI
** Last update Thu Jun 08 11:16:55 2017 Hugo SOSZYNSKI
*/

#include "Socket.hpp"

static void _init()
{
#ifdef WIN32
  WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(err < 0)
    {
        printf("WSAStartup failed !");
        exit(EXIT_FAILURE);
    }
#endif
}

static void _clear()
{
#ifdef WIN32
  WSACleanup();
#endif
}

int main()
{
  _init();

  char buf[5];
  buf[4] = 0;

  mysocket::Socket sock(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  sock.setAddress(htons(42000), htonl(INADDR_ANY));

  if (sock.Bind() == SOCKET_ERROR)
    return 1;
  if (sock.Listen(1) == SOCKET_ERROR)
    return 2;
  if (sock.Accept() == SOCKET_ERROR)
    return 3;
  if (sock.RecvClient<char>(buf, 4, 0) == SOCKET_ERROR)
  {
    sock.closeClientSocket();
    return 4;
  }
  if (sock.SendClient("PONG", 4, 0) == SOCKET_ERROR)
  {
    sock.closeClientSocket();
    return 5;
  }

  sock.closeClientSocket();

  _clear();
  return 0;
}