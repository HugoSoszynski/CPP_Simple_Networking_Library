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

namespace mysocket
{

  Socket::Socket(int domain, int type, int protocol)
    : _domain(domain), _type(type), _protocol(protocol), _socket(-1),
      _clientSocket(-1), _address(NULL), _client(NULL),
      _addressLen(0), _defaultClientLen(0), _clientLen(0)
  {
    this->_socket = socket(domain, type, protocol);
    if (this->_socket == INVALID_SOCKET)
      throw SocketException(strerror(errno));
    if (domain == AF_INET)
    {
      this->_addressLen = sizeof(SOCKADDR_IN);
      this->_defaultClientLen = sizeof(SOCKADDR_IN);
      this->_address = reinterpret_cast<SOCKADDR *>(new SOCKADDR_IN);
      this->_client = reinterpret_cast<SOCKADDR *>(new SOCKADDR_IN);
    }
#if defined (linux)
    else if (domain == AF_UNIX)
    {
      this->_addressLen = sizeof(SOCKADDR_UN);
      this->_defaultClientLen = sizeof(SOCKADDR_UN);
      this->_address = reinterpret_cast<SOCKADDR *>(new SOCKADDR_UN);
      this->_client = reinterpret_cast<SOCKADDR *>(new SOCKADDR_UN);
    }
#endif
    else
    {
      closesocket(this->_socket);
      throw SocketException("ERROR: Socket type not implemented");
    }
    std::memset(this->_address, 0, this->_addressLen);
    std::memset(this->_client, 0, this->_defaultClientLen);
    this->_clientLen = this->_defaultClientLen;
  }

  Socket::~Socket()
  {
    if (this->_domain == AF_INET)
    {
      delete reinterpret_cast<SOCKADDR_IN *>(this->_address);
      delete reinterpret_cast<SOCKADDR_IN *>(this->_client);
    }
#if defined (linux)
    else if (this->_domain == AF_UNIX)
    {
      delete reinterpret_cast<SOCKADDR_UN *>(this->_address);
      delete reinterpret_cast<SOCKADDR_UN *>(this->_client);
    }
#endif
    closesocket(this->_socket);
  }

  void Socket::setAddress(unsigned short sinPort, IN_ADDR sinAddr)
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

  void Socket::closeClientSocket()
  {
    closesocket(this->_clientSocket);
    std::memset(this->_client, 0, this->_defaultClientLen);
    this->_clientLen = this->_defaultClientLen;
  }

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

  int Socket::Accept()
  {
    this->_clientSocket = accept(
      this->_socket,
      this->_client,
      &this->_clientLen
    );
    if (this->_clientSocket == INVALID_SOCKET)
    {
      std::memset(this->_client, 0, this->_defaultClientLen);
      this->_clientLen = this->_defaultClientLen;
      return INVALID_SOCKET;
    }
    return 0;
  }

  template <typename T>
  ssize_t Socket::Send(T const* buf, size_t length, int flags)
  {
    return send(this->_socket, buf, length, flags);
  }

  template <typename T>
  ssize_t Socket::SendClient(T const* buf, size_t length, int flags)
  {
    return send(this->_clientSocket, buf, length, flags);
  }

  template <typename T>
  ssize_t Socket::Recv(T* buf, size_t maxLen, int flags)
  {
    return recv(this->_socket, buf, maxLen, flags);
  }

  template <typename T>
  ssize_t Socket::RecvClient(T* buf, size_t maxLen, int flags)
  {
    return recv(this->_clientSocket, buf, maxLen, flags);
  }
}