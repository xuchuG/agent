#ifndef _EPOLL_H_
#define _EPOLL_H_

#include "connect.h"
#include "cHead.h"

class WritePacManage;
class ReadPacManage;

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
    void init(Connect &conn);//利用dup，同时注册EPOLLIN和EPOLLOUT
    void init(Connect &conn,int state);//epoll_create & all cliSocket add event
    void init(Connect &conn,int state,bool flag);//flag = true 代表为接受和发送数据
    void run();//epoll_wait
    void add_event(void * pm,int fd,int state);
    void modify_event(void * pm,int fd,int state);
    void delete_event(void * pm,int fd,int state);
    
    //get or set
    int getEvCount();
    struct epoll_event* getEpollEvents();
};

#endif
