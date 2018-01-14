/*
** Select.cpp for cpp_indie_studio in /home/god/TEK2/C++/cpp_indie_studio/sources/Network/Select.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Fri Jun 09 12:22:25 2017 Maxime PILLON
** Last update Fri Jun 09 12:22:26 2017 Maxime PILLON
*/

#include <algorithm>
#include <unordered_map>
#include "Select.hpp"


mysocket::Select::Select()
        : maxfd(-1), readfds(), writefds(), exceptfds(), _readfd(),
          _writefd(), _exceptfd(), _timeout(), _selected_timeout() {
    _timeout.tv_sec = 0;
    _timeout.tv_usec = 0;
    _selected_timeout.tv_usec = 0;
    _selected_timeout.tv_sec = 0;
}

mysocket::Select::Select(long tv_sec, long tv_usec)
        : maxfd(-1), readfds(), writefds(), exceptfds(), _readfd(),
          _writefd(), _exceptfd(), _timeout(), _selected_timeout() {
    _timeout.tv_sec = tv_sec;
    _timeout.tv_usec = tv_usec;
    _selected_timeout.tv_usec = 0;
    _selected_timeout.tv_sec = 0;
}

mysocket::Select::~Select() {
    FD_ZERO(&(this->_readfd));
    FD_ZERO(&(this->_writefd));
    FD_ZERO(&(this->_exceptfd));
}

mysocket::Select::Select(Select const& other)
        : maxfd(-1), readfds(), writefds(), exceptfds(), _readfd(),
          _writefd(), _exceptfd(), _timeout(), _selected_timeout() {
    this->_timeout.tv_sec = other._timeout.tv_sec;
    this->_timeout.tv_usec = other._timeout.tv_usec;
    _selected_timeout.tv_usec = 0;
    _selected_timeout.tv_sec = 0;
}

mysocket::Select& mysocket::Select::operator=(Select const& other) {
    this->readfds = other.readfds;
    this->writefds = other.writefds;
    this->exceptfds = other.exceptfds;
    this->_timeout.tv_sec = other._timeout.tv_sec;
    this->_timeout.tv_usec = other._timeout.tv_usec;
    return *this;
}

void mysocket::Select::addReadFd(SOCKET fd) { readfds.push_back(fd); }

void mysocket::Select::addWriteFd(SOCKET fd) { writefds.push_back(fd); }

void mysocket::Select::addExceptFd(SOCKET fd) { exceptfds.push_back(fd); }

void mysocket::Select::removeReadFd(SOCKET fd) {
    auto it = find(readfds.begin(), readfds.end(), fd);
    if (it == readfds.end())
        return;
    readfds.erase(it);
}

void mysocket::Select::removeWriteFd(SOCKET fd) {
    auto it = find(writefds.begin(), writefds.end(), fd);
    if (it == writefds.end())
        return;
    writefds.erase(it);
}

void mysocket::Select::removeExceptFd(SOCKET fd) {
    auto it = find(exceptfds.begin(), exceptfds.end(), fd);
    if (it == exceptfds.end())
        return;
    exceptfds.erase(it);
}

void mysocket::Select::clearReadFd() {
    FD_ZERO(&(this->_readfd));
    readfds.clear();
}

void mysocket::Select::clearWriteFd() {
    FD_ZERO(&(this->_writefd));
    writefds.clear();
}

void mysocket::Select::clearExceptFd() {
    FD_ZERO(&(this->_exceptfd));
    exceptfds.clear();
}

bool mysocket::Select::isFdSetRead(SOCKET fd) {
    return (FD_ISSET(fd, &_readfd));
}

bool mysocket::Select::isFdSetWrite(SOCKET fd) {
    return (FD_ISSET(fd, &_writefd));
}

bool mysocket::Select::isFdSetExcept(SOCKET fd) {
    return (FD_ISSET(fd, &_exceptfd));
}

int mysocket::Select::wait() {
    int ret;

    FD_ZERO(&(this->_readfd));
    FD_ZERO(&(this->_writefd));
    FD_ZERO(&(this->_exceptfd));
    for (auto it : this->readfds) {
        if (it > this->maxfd)
            this->maxfd = it;
        FD_SET(it, &(this->_readfd));
    }
    for (auto it : this->writefds) {
        if (it > this->maxfd)
            this->maxfd = it;
        FD_SET(it, &(this->_writefd));
    }
    for (auto it : this->exceptfds) {
        if (it > this->maxfd)
            this->maxfd = it;
        FD_SET(it, &(this->_exceptfd));
    }
    this->maxfd += 1;
    if (this->_timeout.tv_sec || this->_timeout.tv_usec) {
        this->_selected_timeout.tv_sec = this->_timeout.tv_sec;
        this->_selected_timeout.tv_usec = this->_timeout.tv_usec;
        ret = select(maxfd, &_readfd, &_writefd, &_exceptfd, &_selected_timeout);
    } else
        ret = select(maxfd, &_readfd, &_writefd, &_exceptfd, NULL);
    this->maxfd = -1;
    return ret;
}
