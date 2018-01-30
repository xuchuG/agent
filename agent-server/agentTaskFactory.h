#ifndef _AGENTTASKFACTORY_H_
#define _AGENTTASKFACTORY_H_

#include "./tableManage/agentState.h"
#include "./communicationModule/epoll/tcpEpoller.h"
#include <queue>
using namespace std;
using Queue = queue<pair<char*,char*> >;

class AgentTaskFactory
{
    public:
        void taskDispatch(TcpEpoller* tcp_epoller);
};

#endif

