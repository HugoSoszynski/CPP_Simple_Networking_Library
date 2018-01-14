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

#include "Addr.hpp"

/// \namespace mysocket
namespace mysocket {
    /// \class Socket
    class Socket {

    protected:
        int _domain; //!< Specifies a communication domain, this selects the protocol family which will be used for communication.
        int _type; //!< The socket type which specifies the communication semantics.
        int _protocol; //!< Protocol to be used with the socket.
        SOCKET _socket; //!< The local socket file descriptor.
        std::unique_ptr<InetAddr> _address; //!< The local socket's sockaddr structure.

    public:
        /// \brief Constructor for Socket objects.
        /// \param domain Specifies a communication domain, this selects the protocol family which will be used for communication.
        ///               Could be AF_INET or AF_UNIX (only on linux systems).
        /// \param type The socket has the indicated type, which specifies the communication semantics.
        /// \param protocol The protocol specifies a particular protocol to be used with the socket.
        ///                 Normally only a single protocol exists to support a particular socket type within a given protocol family, in which case protocol can be specified as 0.
        Socket(int domain, int type, int protocol);

        /// \brief Destructor for Socket objects. Close the socket.
        virtual ~Socket();

    protected:
        Socket(int domain, int type, int protocol,
               SOCKET fd, std::unique_ptr<InetAddr>& addr);

    public:
        /// \brief Set the content of the structure used for AF_INET socket.
        ///        NEVER use this method if you use a AF_UNIX socket.
        /// \param sinPort Port to connect to.
        /// \param sinAddr IPv4 address in binary form.
        void setAddress(unsigned short sinPort, std::string const& sinAddr);

        /// \brief Getter for the Socket file descriptor.
        /// \return The socket fd.
        SOCKET getSocketFd() const;

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
        /// \return Upon successful completion, the method shall return the newed socket that must be deleted. Rturn nullptr on error.
        Socket *Accept();

        /// \brief Initiate transmission of a message from the socket to its peer.
        /// \tparam T The type of data to send.
        /// \param buf Point to the buffer containing the message to send.
        /// \param length The length of the message in bytes.
        /// \param flags Specifies the type of message transmission.
        /// \return Upon successful completion, return the number of bytes sent, otherwise return -1.
        template <typename T>
        ssize_t Send(T const& buf, size_t length, int flags = 0);

        template <typename T>
        ssize_t Send(T const* buf, size_t length, int flags = 0);


        /// \brief Initiate reception of a message from the socket to its peer.
        /// \tparam T The type of data to receive.
        /// \param buf Points to the buffer where the message should be stored.
        /// \param maxLen The length of the buffer pointed by the buf argument.
        /// \param flags Specifies the type of message transmission.
        /// \return The length of the received message of successful completion, otherwise return -1.
        template <typename T>
        ssize_t Recv(T& buf, size_t maxLen, int flags = 0);

        template <typename T>
        ssize_t Recv(T* buf, size_t maxLen, int flags = 0);

        /// \brief Used to send data over UNCONNECTED datagram sockets.
        /// \tparam T The type of data to send.
        /// \param msg The data to send.
        /// \param len The length of the data to send.
        /// \param flags Specifies the type of message transmission.
        /// \param to An InetAddr object containing the info of the receiver.
        /// \return The number of bytes sent, otherwise it returns -1 on error.
        template <typename T>
        ssize_t SendTo(T const& msg, size_t len, unsigned int flags, InetAddr& to);

        template <typename T>
        ssize_t SendTo(T const* msg, size_t len, unsigned int flags, InetAddr& to);

        /// \brief Used to receive data from UNCONNECTED datagram sockets.
        /// \tparam T The type of data to receive.
        /// \param buf Points to the buffer where the message should be stored.
        /// \param maxLen The length of the buffer pointed by the buf argument.
        /// \param flags Specifies the type of message transmission.
        /// \param from An empty InetAddr object to be filled with the sender info upon successful completion.
        /// \return The length of the received message of successful completion, otherwise return -1.
        template <typename T>
        ssize_t RecvFrom(T& buf, size_t maxLen, unsigned int flags, InetAddr& from);

        template <typename T>
        ssize_t RecvFrom(T* buf, size_t maxLen, unsigned int flags, InetAddr& from);

    public:

        Socket() = delete;

        Socket(Socket const &other) = delete;

        Socket(Socket const &&other) = delete;

        Socket &operator=(Socket const &other) = delete;

        Socket &operator=(Socket const &&other) = delete;
    };

    template <typename T>
    ssize_t Socket::Send(T const &buf, size_t length, int flags) {
        return send(this->_socket, &buf, length, flags);
    }

    template <typename T>
    ssize_t Socket::Send(T const* buf, size_t length, int flags) {
        return send(this->_socket, buf, length, flags);
    }

    template <typename T>
    ssize_t Socket::Recv(T &buf, size_t maxLen, int flags) {
        return recv(this->_socket, &buf, maxLen, flags);
    }

    template <typename T>
    ssize_t Socket::Recv(T* buf, size_t maxLen, int flags) {
        return recv(this->_socket, buf, maxLen, flags);
    }

    template <typename T>
    ssize_t Socket::SendTo(T const& msg, size_t len, unsigned int flags, InetAddr& to) {
        return sendto(_socket, &msg, len, flags, reinterpret_cast<SOCKADDR*>(&to.GetStruct()), InetAddr::Size);
    }

    template <typename T>
    ssize_t Socket::SendTo(T const* msg, size_t len, unsigned int flags, InetAddr& to) {
        return sendto(_socket, msg, len, flags, reinterpret_cast<SOCKADDR*>(&to.GetStruct()), InetAddr::Size);
    }

    template <typename T>
    ssize_t Socket::RecvFrom(T& buf, size_t maxLen, unsigned int flags, InetAddr& from) {
        socklen_t len {InetAddr::Size};
        return recvfrom(_socket, &buf, maxLen, flags, reinterpret_cast<SOCKADDR*>(&from.GetStruct()), &len);
    }

    template <typename T>
    ssize_t Socket::RecvFrom(T* buf, size_t maxLen, unsigned int flags, InetAddr& from) {
        socklen_t len {InetAddr::Size};
        return recvfrom(_socket, buf, maxLen, flags, reinterpret_cast<SOCKADDR*>(&from.GetStruct()), &len);
    }
}

#endif // !SOCKET_HPP