#ifndef _SUPERVISOR_H_
#define _SUPERVISOR_H_

#include "../../tableManage/agentEpollerManage.h"
#include "epoll.h"
#include "tcpEpoller.h"
#include "listenEpoller.h"
#include <functional>
#include <queue>
using namespace std;
using Queue = queue<pair<char*,char*> >;

class Supervisor{
    private:
        AgentEpollerManage agent_epoller_manage;
        Epoll& epoll;
        std::function<void(TcpEpoller* tcp_epoller)> tcp_epoller_call_back;

    public:
        Supervisor():agent_epoller_manage(),epoll(Epoll::getInstance(agent_epoller_manage)){}

        void run();

        template<class T1>
            void addListenEpoller(int listen_socket){
                 int epoller_id = agent_epoller_manage.generateId();

                epoll.addEvent(epoller_id,listen_socket,EPOLLIN);

                Epoller* epoller = new ListenEpoller(epoller_id,listen_socket,
                        [=](int accept_fd){
                        this->addAgentServerEpoller<T1>(accept_fd);
                });

                if(agent_epoller_manage.insert(epoller_id,epoller) < 0){
                cerr << "agent_epoller_manage::insert error!  epoller_id:" << epoller_id << endl;
                }

            }

        void addThreadPoolSurpervisor(int write_handler);

        template<class T2>
            void addAgentServerEpoller(int accept_fd){
                int epoller_id = agent_epoller_manage.generateId();

                epoll.addEvent(epoller_id,accept_fd,EPOLLIN | EPOLLOUT);

                TcpEpoller* epoller = new T2();
                epoller->init(epoller_id,accept_fd);

                if(agent_epoller_manage.insert(epoller_id,epoller) < 0){
                    cerr << "agent_epoller_manage::insert error!  epoller_id:" << epoller_id << endl;
                }

                cout << "epoller_id :" << epoller_id << endl;

            }

        void addTcpEpollerCallBack(std::function<void(TcpEpoller* tcp_epoller)> call_back);
};

#endif
