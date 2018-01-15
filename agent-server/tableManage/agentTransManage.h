#ifndef _AGENTTRANSMANAGE_H_
#define _AGENTTRANSMANAGE_H_

#include "tableManage.h"
#include "../communicationModule/epoll/epoller.h"

class AgentTransManage : public TableManage<long long,Epoller *>
{
    public:
        AgentTransManage(){}
};

#endif
