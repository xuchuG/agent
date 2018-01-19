#include "epoll.h"
#include "writePacManage.h"
#include "readPacManage.h"

Epoll::Epoll(int socketSizee)
{
  socketSize = socketSizee;
  events = (struct epoll_event *)malloc(sizeof(struct epoll_event)*socketSize*2);
}

Epoll::~Epoll()
{
  free(events);
  close(epollFd);
}

void Epoll::init(Connect & conn)
{
  epollFd = epoll_create(socketSize*2);
  struct epoll_event ev;
  for(int i=1; i<=conn.getSock().size() ;i++)
  {
    WritePacManage * wPac = new WritePacManage(conn.getSock()[i-1],1000000+i-1,0);
    add_event(wPac,wPac->fd,EPOLLOUT);

    int fdDup = dup(conn.getSock()[i-1]);
    ReadPacManage * rPac = new ReadPacManage(fdDup,1000000+i-1,0);
    add_event(rPac,rPac->fd,EPOLLIN);

    wPac->set_rPacPtr(rPac);
    rPac->set_wPacPtr(wPac);
  }
}

/*void Epoll::init(Connect & conn,int state)
{
  epollFd = epoll_create(socketSize);
  struct epoll_event ev;
  for(int i=1; i<=conn.getSock().size() ;i++)
  {
    PacManage * pac = new PacManage(conn.getSock()[i-1],i*111111,0,0);
    add_event(pac,state);

    //
   // pair<map<long long,Sesion>::iterator,bool> ret;
    //Sesion sesion(i*111111);
    //ret = friendRelationMap.insert(pair<long long,Sesion>(i*111111,sesion));
    //if(!ret.second)
    //{
      //cout << "friendRelationMap insert error!\n";
    //}

  }
}*/

/*void Epoll::init(Connect & conn,int state,bool flag)
{
  epollFd = epoll_create(socketSize);
  struct epoll_event ev;
  for(int i=1; i<=conn.getSock().size() ;i++)
  {
    if(flag)
    {
      PacManage * pac = new PacManage(conn.getSock()[i-1],i*111111,0,0,true,true,true,true);
      add_event(pac,state);
    }
  }
}*/

void Epoll::run()
{
  if((evCount = epoll_wait(epollFd,events,socketSize,-1)) == -1)
  {
    cerr << "epoll_wait error!\n";
  }
}

void Epoll::add_event(void * pm,int fd,int state)
{
  struct epoll_event ev;
  ev.events = state;
  ev.data.ptr = pm;
  if(epoll_ctl(epollFd,EPOLL_CTL_ADD,fd,&ev) == -1)
  {
    cerr << "epoll_ctl_add error!\n";
  }
}

void Epoll::modify_event(void * pm,int fd,int state)
{
  struct epoll_event ev;
  ev.events = state;
  ev.data.ptr = pm;
  if(epoll_ctl(epollFd,EPOLL_CTL_MOD,fd,&ev) == -1)
  {
    cerr << "epoll_ctl_mod error!\n";
  }
}

void Epoll::delete_event(void * pm,int fd,int state)
{
  struct epoll_event ev;
  ev.events = state;
  ev.data.ptr = pm;
  if(epoll_ctl(epollFd,EPOLL_CTL_DEL,fd,&ev) == -1)
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

