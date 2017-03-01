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

# include <stdlib.h>
# include <string.h>
# include <string>
# include <unistd.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <sys/types.h>
# include "SocketException.hpp"

class Socket
{
protected:
  int			_domain;
  int			_type;
  int			_protocol;
  int			_socket;
  struct sockaddr_in	_destination;

public:
  Socket(int domain, int type, int protocol);
  ~Socket();

public:
  void Pair(sa_family_t domain, uint16_t portNum, std::string addr);
  void Connect();

private:
  Socket(Socket const& other) = delete;
  Socket(Socket const&& other) = delete;
  Socket& operator=(Socket const& other) = delete;
  Socket& operator=(Socket const&& other) = delete;
};

#endif /* !SOCKET_HPP */