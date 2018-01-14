#ifndef _EPOLL_H_
#define _EPOLL_H_

#include "pacManage.h"
#include <sys/epoll.h>

class Epoll
{
  private:
    int epollFd;//保存epoll描述符
    int socketSize;//最大的事件监听数
    struct epoll_event * events;//监听的所有事件集合
    int evCount;//发生的事件的个数
  public:
    Epoll(int socketSizee);//initial socketSize && events
    ~Epoll();
    void init(int listenSocket);//epoll_create & listenSocket add event
    void run();//epoll_wait
    void add_event(PacManage * pm,int state);
    void modify_event(PacManage * pm,int state);
    void delete_event(PacManage * pm,int state);
    
    //get or set
    int getEvCount();
    struct epoll_event* getEpollEvents();
};

#endif
