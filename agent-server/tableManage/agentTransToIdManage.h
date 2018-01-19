#ifndef _AGENTTRANSTOIDMANAGE_H_
#define _AGENTTRANSTOIDMANAGE_H_

#include "tableManage.h"
#include "../communicationModule/epoll/tcpEpoller.h"

class AgentTransToIdManage : public TableManage<TcpEpoller*,long long>{
    public:
        AgentTransToIdManage(){}
};

#endif
