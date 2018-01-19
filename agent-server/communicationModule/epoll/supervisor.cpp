#include "supervisor.h"
#include "epoller.h"
#include "listenEpoller.h"
#include "agentServerEpoller.h"
#include <iostream>
using namespace std;

void Supervisor::run(){
    while(1){
        epoll.oneRound();
    }
}

void Supervisor::addListenEpoller(int listen_socket){
    int epoller_id = agent_epoller_manage.generateId();

    epoll.addEvent(epoller_id,listen_socket,EPOLLIN);

    Epoller* epoller = new ListenEpoller(epoller_id,listen_socket,
            [=](int accept_fd){
                this->addAgentServerEpoller(accept_fd);
            });

    if(agent_epoller_manage.insert(epoller_id,epoller) < 0){
        cerr << "agent_epoller_manage::insert error!  epoller_id:" << epoller_id << endl;
    }

}

void Supervisor::addAgentServerEpoller(int accept_fd){
    int epoller_id = agent_epoller_manage.generateId();

    epoll.addEvent(epoller_id,accept_fd,EPOLLIN | EPOLLOUT);

    Epoller* epoller = new AgentServerEpoller(epoller_id,accept_fd,tcp_epoller_call_back);

    if(agent_epoller_manage.insert(epoller_id,epoller) < 0){
        cerr << "agent_epoller_manage::insert error!  epoller_id:" << epoller_id << endl;
    }

    cout << "epoller_id :" << epoller_id << endl;
}

void Supervisor::addTcpEpollerCallBack(std::function<void(Queue&,Queue&,TcpEpoller*)> call_back){
    tcp_epoller_call_back = call_back;
}
