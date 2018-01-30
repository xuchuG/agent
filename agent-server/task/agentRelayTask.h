#ifndef AGENTRELAYTASK_H_
#define AGENTREALYTASK_H_

#include "agentBehaviorTask.h"
#include "../communicationModule/epoll/tcpEpoller.h"
#include "../tableManage/agentTransToIdManage.h"
#include "../tableManage/agentState.h"

class AgentRelayTask : public AgentBehaviorTask
{
  private:
    TcpEpoller * tcp_epoller;

  public:
    AgentRelayTask(TcpEpoller * ptr)
    {
        tcp_epoller = ptr;
    }

    ~AgentRelayTask(){}

    virtual void run();
};

#endif

