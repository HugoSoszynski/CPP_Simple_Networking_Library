/*
** Socket.cpp for CPP_Simple_Networking_Library in /home/soszyn_h/Documents/CPP_Simple_Networking_Library/sources/Socket.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Wed Feb 15 19:29:53 2017 Hugo SOSZYNSKI
** Last update Wed Feb 15 19:29:53 2017 Hugo SOSZYNSKI
*/

#include <errno.h>
#include "Socket.hpp"

Socket::Socket(int domain, int type, int protocol)
  : _domain(domain), _type(type), _protocol(protocol)
{
  this->_socket = socket(domain, type, protocol);
  if (this->_socket == -1)
    throw SocketException(strerror(errno));
}

Socket::~Socket()
{}

void Socket::Connect()
{
 if (connect(this->_socket,
	     (struct sockaddr*)&this->_destination,
	     sizeof(struct sockaddr_in)) == -1)
   throw SocketException(strerror(errno));
}