#ifndef CPP_SIMPLE_NETWORKING_LIBRARY_ADDR_HPP
# define CPP_SIMPLE_NETWORKING_LIBRARY_ADDR_HPP

# include <cstdlib>
# include <cstring>
# include <string>
# include <cctype>
# include "SocketException.hpp"

# ifdef WIN32 /* si vous êtes sous Windows */

#  include <winsock2.h>
#  include <windows.h>
#  include <WS2tcpip.h>
#  pragma comment (lib, "Ws2_32.lib")
#  pragma comment (lib, "Mswsock.lib")
#  pragma comment (lib, "AdvApi32.lib")
typedef int ssize_t;

# elif defined (linux) /* si vous êtes sous Linux */

#  include <sys/types.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <sys/un.h>
#  include <arpa/inet.h>
#  include <unistd.h>
#include <bits/unique_ptr.h>

#  define INVALID_SOCKET (-1)
#  define SOCKET_ERROR (-1)
#  define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_un SOCKADDR_UN;
typedef struct sockaddr SOCKADDR;
typedef in_addr_t IN_ADDR;

# else /* sinon vous êtes sur une plateforme non supportée */

#  error not defined for this platform

# endif

namespace mysocket {
    class IAddr {
    public:
        using decl_type = IAddr;
        using type = SOCKADDR;

        static const socklen_t Size{sizeof(type)};
        virtual ~IAddr() = default;
    };

    class InetAddr : public IAddr {
    public:
        using decl_type = InetAddr;
        using type = SOCKADDR_IN;

        static const socklen_t Size{sizeof(type)};

    private:
        type _struct;

    public:
        InetAddr();
        InetAddr(std::string const& address, unsigned short port);
        InetAddr(InetAddr const& other);
        explicit InetAddr(type const& addr_in);
        ~InetAddr() override = default;

        InetAddr& operator=(InetAddr const& other);

        InetAddr& operator=(type const& addr_in);

    public:
        void SetAddress(std::string const& address);
        void SetPort(unsigned short port);

        type& GetStruct();
    };



//#if defined (linux)
//    class UnixAddr : public IAddr {
//    public:
//        using decl_type = UnixAddr;
//        using type = SOCKADDR_UN;
//
//        static const socklen_t Size{sizeof(type)};
//
//    private:
//        type _struct;
//
//    public:
//        UnixAddr() :
//                _struct{0} { _struct.sun_family = AF_UNIX; }
//        UnixAddr(std::string const& address, unsigned short port) :
//                _struct{0} {
//            _struct.sun_family = AF_UNIX;
//            std::strncpy(_struct.sun_path, address.c_str(), 108);
//        }
//        UnixAddr(UnixAddr const& other) : _struct(other._struct) {}
//        explicit UnixAddr(type const& addr_un) :
//                _struct{0} { _struct = addr_un; }
//        ~UnixAddr() override = default;
//
//        UnixAddr& operator=(UnixAddr const& other) {
//            _struct = other._struct;
//            return *this;
//        }
//
//        UnixAddr& operator=(type const& addr_un) { _struct = addr_un; return *this; }
//
//    public:
//        void SetAddress(std::string const& address) { std::strncpy(_struct.sun_path, address.c_str(), 108); }
//
//        type& GetStruct() { return _struct; }
//    };
//#endif
}


#endif // CPP_SIMPLE_NETWORKING_LIBRARY_ADDR_HPP
