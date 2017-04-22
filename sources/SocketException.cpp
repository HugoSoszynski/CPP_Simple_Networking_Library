/*
** SocketException.cpp for CPP_Simple_Networking_Library in /home/soszyn_h/Documents/Projects/CPP_Simple_Networking_Library/sources/SocketException.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Tue Feb 28 18:50:10 2017 Hugo SOSZYNSKI
** Last update Tue Feb 28 18:50:14 2017 Hugo SOSZYNSKI
*/

#include <string>
#include "SocketException.hpp"

namespace mysocket
{

  SocketException::SocketException(std::string const &message) :
    _message(message)
  {}

  SocketException::SocketException(SocketException const &other) :
    _message(other._message)
  {}

  SocketException::~SocketException()
  {}

  SocketException &SocketException::operator=(SocketException const &other)
  {
    this->_message = other._message;
    return *this;
  }

  const char *SocketException::what() const throw()
  {
    return this->_message.c_str();
  }
}
