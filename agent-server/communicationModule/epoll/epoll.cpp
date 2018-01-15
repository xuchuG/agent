#include "epoll.h"

Epoll::Epoll(int socket_sizee,AgentEpollerManage & agent_epoller_managee):
            agent_epoller_manage(agent_epoller_managee){
    socket_size = socket_sizee;
    events = (struct epoll_event *)malloc(sizeof(struct epoll_event)*socketSize);

    epoll_fd = epoll_create(socket_size);
}

Epoll::~Epoll(){
    free(events);
    close(epollFd);
}

Epoll & Epoll::instance(){
    static Epoll single_epoll(MAX_SOCKET_SIZE);
	return single_epoll;
}

/*void Epoll::init(int listenSocket){
  epollFd = epoll_create(socketSize);
  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = listenSocket;
  if(epoll_ctl(epollFd,EPOLL_CTL_ADD,listenSocket,&ev) == -1)
  {
    cerr << "listenSocket:epoll_ctl_add error!\n";
  }
}*/

void Epoll::oneRound()
{
    int event_count;
    if((event_count = epoll_wait(epollFd,events,socketSize,-1)) == -1){
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
    else if(ev.events & EPOLLOUT){
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

void Epoll::modify_event(long long epoller_id,int fd,int state)
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
