#ifndef AGENTLOGINTASK_H_
#define AGENTLOGINTASK_H_

#include "agentBehaviorTask.h"
#include "../communicationModule/epoll/tcpEpoller.h"
#include "../tableManage/agentState.h"
#include "../tableManage/agentTransToIdManage.h"

class AgentLoginTask : public AgentBehaviorTask
{
  private:
    TcpEpoller * tcp_epoller;//通信模块

  public:
    AgentLoginTask(TcpEpoller * ptr)
    {
      tcp_epoller = ptr;
    }
    ~AgentLoginTask(){}

    virtual void run();

};

#endif
