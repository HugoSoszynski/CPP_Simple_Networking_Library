/*
** Socket.hpp for CPP_Simple_Networking_Library in /home/soszyn_h/Documents/CPP_Simple_Networking_Library/includes/Socket.hpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Wed Feb 15 19:29:50 2017 Hugo SOSZYNSKI
** Last update Wed Feb 15 19:29:50 2017 Hugo SOSZYNSKI
*/

#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

class Socket {
protected:
  int			_domain;
  int			_type;
  int			_protocol;
  int			_socket;
  struct sockaddr_in	_destination;

public:
  Socket(int domain, int type, int protocol);
  Socket(Socket const& other);
  ~Socket();

  Socket& operator=(Socket const& other);
  void SocketPair(sa_family_t domain, uint16_t portNum, std::string addr);
  void CreateConnection();
};

#endif /* !SOCKET_HPP */