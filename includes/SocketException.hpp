/*
** SocketException.hpp for CPP_Simple_Networking_Library in /home/soszyn_h/Documents/Projects/CPP_Simple_Networking_Library/includes/SocketException.hpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Tue Feb 28 17:37:17 2017 Hugo SOSZYNSKI
** Last update Tue Feb 28 17:37:17 2017 Hugo SOSZYNSKI
*/

#ifndef SOCKETEXCEPTION_HPP
# define SOCKETEXCEPTION_HPP

# include <exception>
# include <string>

namespace mysocket
{

  class SocketException : public std::exception
  {
  protected:
    std::string _message;

  public:
    SocketException(std::string const &message);

    SocketException(SocketException const &other);

    virtual ~SocketException() throw();

    SocketException &operator=(SocketException const &other);

  public:
    virtual const char *what() const throw();
  };
}

#endif // !SOCKETEXCEPTION_HPP
