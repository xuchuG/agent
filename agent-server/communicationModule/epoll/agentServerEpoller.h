#ifndef _AGENTSERVEREPOLLER_H_
#define _AGENTSERVEREPOLLER_H_

#include "tcpEpoller.h"
#include "../tcpConn/recvPacManage.h"
#include "../tcpConn/sendPacManage.h"
#include <queue>

using Queue = queue<pair<char*,char*> >;

class AgentServerEpoller : public TcpEpoller{
    private:
        Queue recv_que;
        Queue send_que;
        RecvPacManage recv_pac_manage;
        SendPacManage send_pac_manage;

    public:
        AgentServerEpoller(int id,int fd,std::function<void(Queue&,Queue&,TcpEpoller*)> call_back):
            TcpEpoller(id,fd,call_back),recv_pac_manage(fd),send_pac_manage(fd){}
        ~AgentServerEpoller(){}

        virtual void in();
        virtual void out();

        Queue& getSendQue(){
            return send_que;
        }
};

#endif
