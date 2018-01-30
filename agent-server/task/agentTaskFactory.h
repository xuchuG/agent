#ifndef _AGENTTASKFACTORY_H_
#define _AGENTTASKFACTORY_H_

#include "../tableManage/agentState.h"
#include "../communicationModule/epoll/tcpEpoller.h"
using namespace std;

class AgentTaskFactory
{
    public:
        void taskDispatch(TcpEpoller* tcp_epoller);
};

#endif

