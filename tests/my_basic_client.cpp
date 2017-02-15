/*
** my_basic_client.cpp for CPP_Simple_Networking_Library in /home/soszyn_h/Documents/CPP_Simple_Networking_Library/tests/my_basic_client.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Wed Feb 15 20:05:18 2017 Hugo SOSZYNSKI
** Last update Wed Feb 15 20:05:18 2017 Hugo SOSZYNSKI
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAXRCVLEN 500
#define PORTNUM 42000

int main()
{
  char buf[MAXRCVLEN + 1];
  int my_socket;
  struct sockaddr_in dest;
  ssize_t len;

  my_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (my_socket == -1)
    return 1;

  memset(&dest, 0, sizeof(struct sockaddr_in));

  dest.sin_family = AF_INET;
  dest.sin_addr.s_addr = inet_addr("10.26.111.64");
  dest.sin_port = htons(PORTNUM);

  if (
    connect(my_socket, (struct sockaddr*)&dest, sizeof(struct sockaddr_in))
    == -1)
    return 2;

  len = recv(my_socket, buf, MAXRCVLEN, 0);
  if (len == -1)
    return 3;

  buf[len] = '\0';
  printf("%s\n", buf);

  send(my_socket, "PONG", 4, 0);

  close(my_socket);
  return (0);
}