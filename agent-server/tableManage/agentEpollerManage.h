#ifndef _AGENTEPOLLERMANAGE_H_
#define _AGENTEPOLLERMANAGE_H_

#include "tableManage.h"
#include "../communicationModule/epoll/epoller.h"

class AgentEpollerManage : public TableManage<long long,Epoller*>{
    public:
        AgentEpollerManage(){}
};

#endif
