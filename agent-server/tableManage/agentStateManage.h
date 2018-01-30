#ifndef _AGENTSTATEMANAGE_H_
#define _AGENTSTATEMANAGE_H_

#include "tableManage.h"
#include "agentState.h"
#include "../communicationModule/epoll/tcpEpoller.h"

class AgentStateManage : public TableManage<TcpEpoller*,AgentState *>
{
    public:
        AgentStateManage(){}
};

#endif
