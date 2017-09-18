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
#include <iostream>
#include "Socket.hpp"

namespace mysocket
{

  Socket::Socket(int domain, int type, int protocol)
    : _domain(domain), _type(type), _protocol(protocol), _socket(-1),
      _address(nullptr), _addressLen(0)
  {
    this->_socket = socket(domain, type, protocol);
    if (this->_socket == INVALID_SOCKET)
      throw SocketException(strerror(errno));
    if (domain == AF_INET)
    {
      this->_addressLen = sizeof(SOCKADDR_IN);
      this->_address = reinterpret_cast<SOCKADDR *>(new SOCKADDR_IN);
    }
#if defined (linux)
    else if (domain == AF_UNIX)
    {
      this->_addressLen = sizeof(SOCKADDR_UN);
      this->_address = reinterpret_cast<SOCKADDR *>(new SOCKADDR_UN);
    }
#endif
    else
    {
      closesocket(this->_socket);
      throw SocketException("ERROR: Socket type not implemented");
    }
    std::memset(this->_address, 0, this->_addressLen);
  }

  Socket::Socket(int domain, int type, int protocol,
		 SOCKET fd, SOCKADDR_IN const& addr, socklen_t len)
    :_domain(domain), _type(type), _protocol(protocol), _socket(fd),
     _address(nullptr), _addressLen(len)
  {
    SOCKADDR_IN *new_addr;

    new_addr = new SOCKADDR_IN;
    new_addr->sin_port = addr.sin_port;
    new_addr->sin_addr = addr.sin_addr;
    new_addr->sin_family = addr.sin_family;
    this->_address = reinterpret_cast<SOCKADDR *>(new_addr);
  }

  Socket::Socket(int domain, int type, int protocol,
		 SOCKET fd, SOCKADDR_UN const& addr, socklen_t len)
    :_domain(domain), _type(type), _protocol(protocol), _socket(fd),
     _address(nullptr), _addressLen(len)
  {
    SOCKADDR_UN *new_addr;

    new_addr = new SOCKADDR_UN;
    new_addr->sun_family = addr.sun_family;
    std::memcpy(new_addr->sun_path, addr.sun_path, 108); // 108 RTFM
    this->_address = reinterpret_cast<SOCKADDR *>(new_addr);
  }

  Socket::~Socket()
  {
    if (this->_domain == AF_INET)
      delete reinterpret_cast<SOCKADDR_IN *>(this->_address);
#if defined (linux)
    else if (this->_domain == AF_UNIX)
      delete reinterpret_cast<SOCKADDR_UN *>(this->_address);
#endif
    closesocket(this->_socket);
  }

#ifdef WIN32
  void Socket::setAddress(unsigned short sinPort, unsigned long sinAddr)
#elif defined (linux)
  void Socket::setAddress(unsigned short sinPort, IN_ADDR sinAddr)
#endif
  {
    SOCKADDR_IN *addr;

    addr = reinterpret_cast<SOCKADDR_IN *>(this->_address);
    addr->sin_family = AF_INET;
    addr->sin_port = sinPort;
    addr->sin_addr.s_addr = sinAddr;
  }

  void Socket::setAddress(std::string const &pathname)
  {
#if defined (linux)
    SOCKADDR_UN *addr;

    addr = reinterpret_cast<SOCKADDR_UN *>(this->_address);
    addr->sun_family = AF_UNIX;
    std::strncpy(
      addr->sun_path,
      pathname.c_str(),
      108 // addr->sun_path[108] (RTFM)
    );
#endif
  }

  SOCKET Socket::getSocketFd() const { return this->_socket; }

  int Socket::Connect()
  {
    return connect(
      this->_socket,
      this->_address,
      this->_addressLen
    );
  }

  int Socket::Bind()
  {
    return bind(
      this->_socket,
      this->_address,
      this->_addressLen
    );
  }

  int Socket::Listen(int backlog)
  {
    return listen(this->_socket, backlog);
  }

  Socket* Socket::Accept()
  {
#if defined (linux)
    if (this->_domain == AF_UNIX)
    {
      SOCKET sock;
      SOCKADDR_UN addr;
      socklen_t len = sizeof(addr);

      sock = accept(this->_socket, reinterpret_cast<SOCKADDR*>(&addr), &len);
      if (sock == -1)
	return nullptr;
      Socket *client = new Socket(this->_domain, this->_type, this->_protocol,
				  sock, addr, len);
      return client;
    }
#endif
    SOCKET sock;
    SOCKADDR_IN addr;
    socklen_t len = sizeof(addr);

    sock = accept(this->_socket, reinterpret_cast<SOCKADDR*>(&addr), &len);
    if (sock == -1)
      return nullptr;
    Socket *client = new Socket(this->_domain, this->_type, this->_protocol,
				sock, addr, len);
    return client;
  }

#ifdef WIN32
  ssize_t Socket::Send(char const* buf, size_t length, int flags)
#elif defined (linux)
  ssize_t Socket::Send(void const* buf, size_t length, int flags)
#endif
  {
    return send(this->_socket, buf, length, flags);
  }

#ifdef WIN32
  ssize_t Socket::Recv(char* buf, size_t maxLen, int flags)
#elif defined (linux)
  ssize_t Socket::Recv(void* buf, size_t maxLen, int flags)
#endif
  {
    return recv(this->_socket, buf, maxLen, flags);
  }
}
