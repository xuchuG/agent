#include "supervisor.h"
#include "epoller.h"
#include "../../threadPool/threadPoolSurpervisor.h"
#include <iostream>
using namespace std;

extern ThreadPoolSurpervisor * g_thread_pool_surpervisor;

void Supervisor::run(){
    while(1){
        epoll.oneRound();
    }
}

void Supervisor::addThreadPoolSurpervisor(int write_handler){
    int epoller_id = agent_epoller_manage.generateId();

    epoll.addEvent(epoller_id,write_handler,EPOLLIN | EPOLLOUT);

    g_thread_pool_surpervisor = new ThreadPoolSurpervisor(epoller_id,write_handler);

    if(agent_epoller_manage.insert(epoller_id,(Epoller *)g_thread_pool_surpervisor) < 0){
        cerr << "agent_epoller_manage::insert error!  epoller_id:" << epoller_id << endl;
    }
}

/*void Supervisor::addTcpEpollerCallBack(std::function<void(TcpEpoller*)> call_back){
    tcp_epoller_call_back = call_back;
}*/
