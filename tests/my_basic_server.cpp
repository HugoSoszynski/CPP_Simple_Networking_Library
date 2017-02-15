/*
** my_basic_server.cpp for CPP_Simple_Networking_Library in /home/god/TEK2/PersonalProject/CPP_Simple_Networking_Library/tests/my_basic_server.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Wed Feb 15 20:05:16 2017 Maxime PILLON
** Last update Wed Feb 15 20:05:16 2017 Maxime PILLON
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORTNUM 42000
#define MAXRCVLEN 500

int main(int argc, char **argv)
{
  char *msg = "PING";

  struct sockaddr_in dest;
  struct sockaddr_in serv;
  int mysocket;
  socklen_t socksize = sizeof(struct sockaddr_in);

  memset(&serv, 0, sizeof(serv));
  serv.sin_family = AF_INET;
  serv.sin_addr.s_addr = htonl(INADDR_ANY);
  serv.sin_port = htons(PORTNUM);

  if ((mysocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (1);

  bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));

  if (listen(mysocket, 1) == -1)
    return (-1);

  int consocket;
  if ((consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize)) == -1)
    return 1;

  while(consocket)
  {
    send(consocket, msg, strlen(msg), 0);
    char buf[MAXRCVLEN + 1];
    int len = recv(consocket, buf, MAXRCVLEN, 0);
    if (len == -1)
      return (1);
    buf[len] = '\0';
    printf("%s\n", buf);
    close(consocket);
    consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
  }
  close(mysocket);
  return EXIT_SUCCESS;
}