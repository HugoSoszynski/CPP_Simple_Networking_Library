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

namespace socket
{

  Socket::Socket(int domain, int type, int protocol)
    : _domain(domain), _type(type), _protocol(protocol), _socket(-1),
      _clientSocket(-1), _address(NULL), _client(NULL),
      _addressLen(0), _clientLen(0)
  {
    if (type == AF_INET)
    {
      this->_addressLen = sizeof(sockaddr_in);
      this->_clientLen = sizeof(sockaddr_in);
      this->_address = reinterpret_cast<sockaddr*>(new sockaddr_in);
      this->_client = reinterpret_cast<sockaddr*>(new sockaddr_in);
    }
    else if (type == AF_UNIX)
    {
      this->_addressLen = sizeof(sockaddr_un);
      this->_clientLen = sizeof(sockaddr_un);
      this->_address = reinterpret_cast<sockaddr*>(new sockaddr_un);
      this->_client = reinterpret_cast<sockaddr*>(new sockaddr_un);
    }
    else
      throw SocketException("ERROR: Socket type not implemented");
    std::memset(this->_address, 0, this->_addressLen);
    std::memset(this->_client, 0, this->_clientLen);
    this->_socket = socket(domain, type, protocol);
    if (this->_socket == -1)
      throw SocketException(strerror(errno));
  }

  Socket::~Socket()
  {
    if (this->_type == AF_INET)
    {
      delete reinterpret_cast<sockaddr_in*>(this->_address);
      delete reinterpret_cast<sockaddr_in*>(this->_client);
    }
    else if (this->_type == AF_UNIX)
    {
      delete reinterpret_cast<sockaddr_un*>(this->_address);
      delete reinterpret_cast<sockaddr_un*>(this->_client);
    }
    close(this->_socket);
  }

  void Socket::setInAddress(unsigned short sinPort, struct in_addr sinAddr)
  {
    sockaddr_in* addr;

    addr = reinterpret_cast<sockaddr_in*>(this->_address);
    addr->sin_family = AF_INET;
    addr->sin_port = sinPort;
    addr->sin_addr = sinAddr;
  }

  void Socket::setUnAddress(std::string const &pathname)
  {
    sockaddr_un* addr;

    addr = reinterpret_cast<sockaddr_un*>(this->_address);
    addr->sun_family = AF_UNIX;
    std::strncpy(addr->sun_path, pathname.c_str(), 108); // addr->sun_path[108] (RTFM)
  }

  void Socket::closeClientSocket()
  {
    close(this->_clientSocket);
    std::memset(this->_client, 0, this->_clientLen);
  }

  int Socket::Connect()
  {
    return connect(this->_socket,
		   this->_address,
		   this->_addressLen);
  }
}