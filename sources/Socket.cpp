/*
** Socket.cpp for CPP_Simple_Networking_Library in /home/soszyn_h/Documents/CPP_Simple_Networking_Library/sources/Socket.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Wed Feb 15 19:29:53 2017 Hugo SOSZYNSKI
** Last update Wed Feb 15 19:29:53 2017 Hugo SOSZYNSKI
*/

#include "Socket.hpp"

Socket::Socket(int domain, int type, int protocol)
  : _domain(domain), _type(type), _protocol(protocol)
{
  this->_socket = socket(domain, type, protocol);
}

Socket::Socket(Socket const &other)
{
  this->_domain = other._domain;
  this->_protocol = other._protocol;
  this->_socket = other._socket;
  this->_type = other._type;
}

Socket::~Socket()
{
  close(_socket);
}

Socket& Socket::operator=(Socket const &other)
{
  this->_domain = other._domain;
  this->_protocol = other._protocol;
  this->_socket = other._socket;
  this->_type = other._type;
}

void Socket::SocketPair(sa_family_t domain, uint16_t portNum, std::string addr)
{
  // check error
  memset(&this->_destination, 0, sizeof(struct sockaddr_in));
  this->_destination.sin_family = domain;
  this->_destination.sin_port = htons(portNum); // check error
  this->_destination.sin_addr.s_addr = inet_addr(addr.c_str()); // check error
}

void Socket::CreateConnection()
{
 connect(this->_socket, (struct sockaddr*)&this->_destination, sizeof(struct sockaddr_in)); // check error
}