#include "Addr.hpp"

namespace mysocket {

    InetAddr::InetAddr() {
        _struct.sin_family = AF_INET;
    }

    InetAddr::InetAddr(std::string const& address, unsigned short port) {
        _struct.sin_family = AF_INET;
        _struct.sin_addr.s_addr = inet_addr(address.c_str());
        _struct.sin_port = htons(port);
    }

    InetAddr::InetAddr(InetAddr const& other) : _struct(other._struct) {}

    InetAddr::InetAddr(type const& addr_in) {
        _struct = addr_in;
    }

    InetAddr& InetAddr::operator=(InetAddr const& other) {
        _struct = other._struct;
        return *this;
    }

    InetAddr& InetAddr::operator=(type const& addr_in) {
        _struct = addr_in;
        return *this;
    }

    void InetAddr::SetAddress(std::string const& address) {
        _struct.sin_addr.s_addr = inet_addr(address.c_str());
    }

    void InetAddr::SetPort(unsigned short port) {
        _struct.sin_port = htons(port);
    }

    InetAddr::type& InetAddr::GetStruct() {
        return _struct;
    }

}