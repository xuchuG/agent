#include "cHead.h"
#include "epoll.h"

Epoll::Epoll(int socketSizee)
{
  socketSize = socketSizee;
  events = (struct epoll_event *)malloc(sizeof(struct epoll_event)*socketSize);
}

Epoll::~Epoll()
{
  free(events);
  close(epollFd);
}

void Epoll::init(int listenSocket)
{
  epollFd = epoll_create(socketSize);
  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = listenSocket;
  if(epoll_ctl(epollFd,EPOLL_CTL_ADD,listenSocket,&ev) == -1)
  {
    cerr << "listenSocket:epoll_ctl_add error!\n"; 
  }  
}

void Epoll::run()
{
  if((evCount = epoll_wait(epollFd,events,socketSize,-1)) == -1)
  {
    cerr << "epoll_wait error!\n";
  }
}

void Epoll::add_event(PacManage * pm,int state)
{
  struct epoll_event ev;
  ev.events = state;
  ev.data.ptr = pm;
  if(epoll_ctl(epollFd,EPOLL_CTL_ADD,pm->fd,&ev) == -1)
  {
    cerr << "epoll_ctl_add error!\n";
  }
}

void Epoll::modify_event(PacManage * pm,int state)
{
  struct epoll_event ev;
  ev.events = state;
  ev.data.ptr = pm;
  if(epoll_ctl(epollFd,EPOLL_CTL_MOD,pm->fd,&ev) == -1)
  {
    cerr << "epoll_ctl_mod error!\n";
  }
}

void Epoll::delete_event(PacManage * pm,int state)
{
  struct epoll_event ev;
  ev.events = state;
  ev.data.ptr = pm;
  if(epoll_ctl(epollFd,EPOLL_CTL_DEL,pm->fd,&ev) == -1)
  {
    cerr << "epoll_ctl_del error!\n";
  }
}

int Epoll::getEvCount()
{
  return evCount;
}

struct epoll_event * Epoll::getEpollEvents()
{
  return events;
}

