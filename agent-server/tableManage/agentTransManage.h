#ifndef _AGENTTRANSMANAGE_H_
#define _AGENTTRANSMANAGE_H_

#include "tableManage.h"
#include "../communicationModule/epoll/tcpEpoller.h"

class AgentTransManage : public TableManage<long long,TcpEpoller *>
{
    public:
        AgentTransManage(){}
};

#endif
