#ifndef AGENTQUERYTASK_H_
#define AGENTQUERYTASK_H_

#include "agentBehaviorTask.h"
#include "../communicationModule/epoll/tcpEpoller.h"
#include "../tableManage/agentState.h"

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
