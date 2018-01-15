#include "epoller.h"

Epoller::Epoller(int idd,int fdd){
    this->id_ = idd;
    this->fd_ = fd;
}

int Epoller::getFd()
{
    return this->fd_;
}
