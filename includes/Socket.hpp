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

# include <cstdlib>
# include <cstring>
# include <string>
# include <unistd.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <ctype.h>
# include <sys/un.h>
# include "SocketException.hpp"

/// \namespace mysocket
namespace mysocket
{
  /// \class Socket
  class Socket
  {
  protected:
    int _domain; //!< Specifies a communication domain, this selects the protocol family which will be used for communication.
    int _type; //!< The socket type which specifies the communication semantics.
    int _protocol; //!< Protocol to be used with the socket.
    int _socket; //!< The local socket file descriptor.
    int _clientSocket; //!< The client socket (not initialized by default).
    struct sockaddr *_address; //!< The local socket's sockaddr structure.
    struct sockaddr *_client; //!< The client socket's sockaddr structure.
    socklen_t _addressLen; //!< The local sockaddr length.
    socklen_t _defaultClientLen; //!< The original client's sockaddr length.
    socklen_t _clientLen; //!< The client's sockaddr length.

  public:
    /// \brief Constructor for Socket objects.
    /// \param domain Specifies a communication domain, this selects the protocol family which will be used for communication.
    ///               Could be AF_INET or AF_UNIX.
    /// \param type The socket has the indicated type, which specifies the communication semantics.
    /// \param protocol The protocol specifies a particular protocol to be used with the socket.
    ///                 Normally only a single protocol exists to support a particular socket type within a given protocol family, in which case protocol can be specified as 0.
    Socket(int domain, int type, int protocol);

    /// \brief Destructor for Socket objects. Close the socket.
    virtual ~Socket();

  public:
    /// \brief Set the content of the structure used for AF_INET socket.
    ///        NEVER use this method if you use a AF_UNIX socket.
    /// \param sinPort Port to connect to.
    /// \param sinAddr IPv4 address in binary form.
    void setInAddress(unsigned short sinPort, struct in_addr sinAddr);

    /// \brief Set the content of the structure used for AF_UNIX socket.
    ///        NEVER use this method if you use a AF_INET socket.
    /// \param pathname The pathname for the socket (max 108 char, else will be truncated).
    void setUnAddress(std::string const& pathname);

    /// \brief Close the client socket. If the socket was not open, undefined behaviour may occur.
    void closeClientSocket();

  public:
    /// \brief Attempt to make a connection on a connection-mode socket or to set or reset the peer address of a connectionless-mode socket.
    /// \return Upon successful completion, this method shall return 0; otherwise, −1 shall be returned.
    int Connect();

    /// \brief Assign a local socket address to the socket.
    /// \return Upon successful completion, the method shall return 0; otherwise, −1 shall be returned.
    int Bind();

    /// \brief Mark a connection-mode socket as accepting connections.
    /// \param backlog The maximum number of connection to the socket (MUST be LESS than SOMAXCONN defined in <sys/socket.h>)
    /// \return Upon successful completion, the method shall return 0; otherwise, −1 shall be returned.
    int Listen(int backlog);

    /// \brief Extract the first connection on the queue of pending connections and allocate a new file descriptor for that socket (here the clientSocket of the class).
    /// \return Upon successful completion, the method shall return 0; otherwise, −1 shall be returned.
    int Accept();

    /// \brief Initiate transmission of a message from the socket to its peer (used by clients).
    /// \param buf Point to the buffer containing the message to send.
    /// \param length The length of the message in bytes.
    /// \param flags Specifies the type of message transmission.
    /// \return Upon successful completion, return the number of bytes sent, otherwise return -1.
    ssize_t Send(void const* buf, size_t length, int flags);

    /// \brief Initiate transmission of a message from the socket to its peer (used by server).
    /// \param buf Point to the buffer containing the message to send.
    /// \param length The length of the message in bytes.
    /// \param flags Specifies the type of message transmission.
    /// \return Upon successful completion, return the number of bytes sent, otherwise return -1.
    ssize_t SendClient(void const* buf, size_t length, int flags);

    /// \brief
    /// \param buf Points to the buffer where the message should be stored.
    /// \param maxLen The length of the buffer pointed by the buf argument.
    /// \param flags Specifies the type of message transmission.
    /// \return The length of the received message of successful completion, otherwise return -1.
    ssize_t Recv(void *buf, size_t maxLen, int flags);

  private:
    Socket(Socket const &other) = delete;

    Socket(Socket const &&other) = delete;

    Socket &operator=(Socket const &other) = delete;

    Socket &operator=(Socket const &&other) = delete;
  };
}

#endif /* !SOCKET_HPP */