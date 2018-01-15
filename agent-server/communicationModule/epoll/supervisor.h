#ifndef _SUPERVISOR_H_
#define _SUPERVISOR_H_

#include "../../tableManage/agentEpollerManage.h"
#include "epoll.h"

class Supervisor{
    private:
        AgentEpollerManage & agent_epoller_manage;
        Epoll & epoll;

    public:
        Supervisor():agent_epoller_manage(),epoll(agent_epoller_manage){}

};

#endif
