/*
** Select.hpp for cpp_indie_studio in /home/soszyn_h/rendu/CPP/cpp_indie_studio/includes/Network/Select.hpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Fri Jun 09 09:15:15 2017 Hugo SOSZYNSKI
** Last update Fri Jun 09 09:15:15 2017 Hugo SOSZYNSKI
*/

#ifndef SELECT_HPP
# define SELECT_HPP

# ifdef WIN32

#  include <winsock2.h>
#  include <windows.h>
#  include <WS2tcpip.h>
#  pragma comment (lib, "Ws2_32.lib")
#  pragma comment (lib, "Mswsock.lib")
#  pragma comment (lib, "AdvApi32.lib")

# elif defined (linux)

#  include <sys/select.h>

typedef int SOCKET;

# endif

#include <vector>

/// \namespace mysocket
namespace mysocket {
    /// \class Select
    /// \brief Select encapsulation for c++.
    ///        The user does not have to care about fd_sets or timeout reset.
    ///        The class take care of the repetitive parts.
    class Select {
    public:
        /// \brief Select class default constructor, set the timeout to 0.
        Select();

        /// \brief Select class constructor
        /// \param tv_sec Select timeout in seconds (added to the usec).
        /// \param tv_usec Select timeout in micro-seconds (added to sec).
        Select(long tv_sec, long tv_usec);

        /// \brief Select destructor.
        ~Select();

        /// \brief Select copy constructor. Only the timeout and all the fds are copied.
        /// \param other The Select object to create.
        Select(Select const &other);

        /// \brief Select copy operator. Only the timeout and all the fds are copied.
        /// \param other Select object to copy.
        /// \return Reference to the copied object.
        Select &operator=(Select const &other);

    public:
        /// \brief Add a fd to the readfds fd_set of the select.
        /// \param fd The file descriptor to add.
        void addReadFd(SOCKET fd);

        /// \brief Add a fd to the writefds fd_set of the select.
        /// \param fd The file descriptor to add.
        void addWriteFd(SOCKET fd);

        /// \brief Add a fd to the writefds fd_set of the select.
        /// \param fd The file descriptor to add.
        void addExceptFd(SOCKET fd);

        /// \brief Remove a fd to the readfds fd_set of the select.
        /// \param fd The file descriptor to remove.
        void removeReadFd(SOCKET fd);

        /// \brief Remove a fd to the writefds fd_set of the select.
        /// \param fd The file descriptor to remove.
        void removeWriteFd(SOCKET fd);

        /// \brief Remove a fd to the exceptfds fd_set of the select.
        /// \param fd The file descriptor to remove.
        void removeExceptFd(SOCKET fd);

        /// \brief Empty the select readfds.
        void clearReadFd();

        /// \brief Empty the select writefds.
        void clearWriteFd();

        /// \brief Empty the select exceptfds.
        void clearExceptFd();

        /// \brief Check if the fd Read is usable after a select action.
        /// \param fd The fd to check.
        /// \return true if the fd is usable, false otherwise.
        bool isFdSetRead(SOCKET fd);

        /// \brief Check if the fd Write is usable after a select action.
        /// \param fd The fd to check.
        /// \return true if the fd is usable, false otherwise.
        bool isFdSetWrite(SOCKET fd);

        /// \brief Check if the fd Except is usable after a select action.
        /// \param fd The fd to check.
        /// \return true if the fd is usable, false otherwise.
        bool isFdSetExcept(SOCKET fd);

        /// \brief Start the select action and wait until a fd state changed or the timeout is done.
        /// \return The number of file descriptors contained in the three returned descriptor sets.
        ///         Zero if the timeout expires before anything interesting happens. On error, -1 is returned.
        int wait();

    protected:
        SOCKET maxfd;
        std::vector<SOCKET> readfds;
        std::vector<SOCKET> writefds;
        std::vector<SOCKET> exceptfds;

        fd_set _readfd;
        fd_set _writefd;
        fd_set _exceptfd;
        struct timeval _timeout;
        struct timeval _selected_timeout;
    };
}

#endif /* !SELECT_HPP */
