#ifndef AGENTQUERYTASK_H_
#define AGENTQUERYTASK_H_

#include <queue>

#include "agentBehaviorTask.h"
#include "./communicationModule/epoll/tcpEpoller.h"
#include "./tableManage/agentState.h"

using Queue = queue<pair<char*,char*> >;

class AgentQueryTask : public AgentBehaviorTask
{
  private:
    TcpEpoller * tcp_epoller;

  public:
    AgentQueryTask(TcpEpoller * ptr)
    {
      tcp_epoller = ptr;
    }
    ~AgentQueryTask(){}

    virtual void run();
};


#endif
