#include "epoller.h"

Epoller::Epoller(int id,int fd){
    this->id_ = id;
    this->fd_ = fd;
}

void Epoller::setId(long long id){
    this->id_ = id;
}

long long Epoller::getId(){
    return this->id_;
}

void Epoller::setFd(int fd){
    this->fd_ = fd;
}

int Epoller::getFd()
{
    return this->fd_;
}
