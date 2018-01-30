#include "epoll.h"
#include <unistd.h>

Epoll::~Epoll(){
    free(events);
    close(epoll_fd);
}

Epoll & Epoll::getInstance(AgentEpollerManage& agent_epoller_manage){
    static Epoll single_epoll(MAX_SOCKET_SIZE,agent_epoller_manage);
    return single_epoll;
}

void Epoll::oneRound()
{
    int event_count;
    if((event_count = epoll_wait(epoll_fd,events,socket_size,-1)) == -1){
        cerr << "epoll_wait error!\n";
    }

    for(int i=0; i<event_count; i++){
        handOneEvent(events[i]);
    }
}

void Epoll::handOneEvent(struct epoll_event ev){
    int epoller_id = ev.data.u64;
    Epoller * epoller = agent_epoller_manage.find(epoller_id);

    if(ev.events & EPOLLIN){
        epoller->in();
    }
    if(ev.events & EPOLLOUT){
        epoller->out();
    }

}

void Epoll::addEvent(long long epoller_id,int fd,int state)
{
  struct epoll_event ev;
  ev.events = state;
  ev.data.u64 = epoller_id;
  if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,fd,&ev) == -1)
  {
    cerr << "epoll_ctl_add error!\n";
  }
}

void Epoll::modifyEvent(long long epoller_id,int fd,int state)
{
  struct epoll_event ev;
  ev.events = state;
  ev.data.u64 = epoller_id;
  if(epoll_ctl(epoll_fd,EPOLL_CTL_MOD,fd,&ev) == -1)
  {
    cerr << "epoll_ctl_mod error!\n";
  }
}

void Epoll::deleteEvent(long long epoller_id,int fd,int state)
{
  struct epoll_event ev;
  ev.events = state;
  ev.data.u64 = epoller_id;
  if(epoll_ctl(epoll_fd,EPOLL_CTL_DEL,fd,&ev) == -1)
  {
    cerr << "epoll_ctl_del error!\n";
  }
}
