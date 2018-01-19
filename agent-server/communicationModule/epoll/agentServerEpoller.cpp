#include "agentServerEpoller.h"
#include <iostream>
#include "epoll.h"
using namespace std;

void AgentServerEpoller::in(){
    if(recv_pac_manage.recvPac(recv_que) == 0){//整包接收完
        tcp_epoller_call_back(recv_que,send_que,this);
    }
}

void AgentServerEpoller::out(){
    if(send_que.empty()){
        return;
    }

    send_pac_manage.sendPac(send_que);
}
