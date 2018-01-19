#include "epoller.h"

Epoller::Epoller(long long idd,int fdd){
    this->id_ = idd;
    this->fd_ = fdd;
}

long long Epoller::getId(){
    this->id_;
}

int Epoller::getFd()
{
    return this->fd_;
}
