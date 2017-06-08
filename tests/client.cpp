/*
** client.cpp for CPP_Simple_Networking_Library in /home/soszyn_h/Documents/Projects/CPP_Simple_Networking_Library/tests/client.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Thu Jun 08 10:58:23 2017 Hugo SOSZYNSKI
** Last update Thu Jun 08 10:58:23 2017 Hugo SOSZYNSKI
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
  sock.setAddress(htons(42000), inet_addr("127.0.0.1"));
  if (sock.Connect() == SOCKET_ERROR)
    return 1;
  if (sock.Send("PING", 4) == SOCKET_ERROR)
    return 2;
  if (sock.Recv(buf, 4, 0) == SOCKET_ERROR)
    return 3;
  printf("%s\n", buf);

  _clear();
  return 0;
}