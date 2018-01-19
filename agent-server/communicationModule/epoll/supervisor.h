#ifndef _SUPERVISOR_H_
#define _SUPERVISOR_H_

#include "../../tableManage/agentEpollerManage.h"
#include "epoll.h"
#include "tcpEpoller.h"
#include <functional>
#include <queue>
using namespace std;
using Queue = queue<pair<char*,char*> >;

class Supervisor{
    private:
        AgentEpollerManage agent_epoller_manage;
        Epoll& epoll;
        std::function<void(Queue& recv_que,Queue& send_que,TcpEpoller* tcp_epoller)> tcp_epoller_call_back;

    public:
        Supervisor():agent_epoller_manage(),epoll(Epoll::getInstance(agent_epoller_manage)){}

        void run();
        void addListenEpoller(int listen_socket);
        void addAgentServerEpoller(int accept_fd);
        void addTcpEpollerCallBack(std::function<void(Queue& recv_que,Queue& send_que,TcpEpoller* tcp_epoller)> call_back);
};

#endif
