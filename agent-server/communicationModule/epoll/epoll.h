#ifndef _EPOLL_H_
#define _EPOLL_H_

//单例模式

#include "epoller.h"
#include "../../tableManage/agentEpollerManage.h"
#include <sys/epoll.h>

#define MAX_SOCKET_SIZE 1000

class Epoll{
    private:
        int epoll_fd;//保存epoll描述符
        int socket_size;//最大的事件监听数
        struct epoll_event * events;//监听的所有事件集合

       AgentEpollerManage & agent_epoller_manage;

    private:
        Epoll(int socket_sizee,AgentEpollerManage agent_epoller_managee);
        Epoll(Epoll const &){}
        Epoll & operator=(Epoll const &){}
        ~Epoll();

    public:
        static Epoll & instance();
        //void init(int listenSocket);//epoll_create & listenSocket add event
        void oneRound();
        void handOneEvent(struct epoll_event ev);

        void addEvent(long long epoller_id,int fd,int state);
        void modifyEvent(long long epoller_id,int fd,int state);
        void deleteEvent(long long epoller_id,int state);

};

#endif
