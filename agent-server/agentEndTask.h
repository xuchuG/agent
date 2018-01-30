#ifndef _AGENTENDTASK_H_
#define _AGENTENDTASK_H_

#include <queue>

#include "agentBehaviorTask.h"
#include "./communicationModule/epoll/tcpEpoller.h"

using Queue = queue<pair<char*,char*> >;

class AgentEndTask : public AgentBehaviorTask
{
  private:
    TcpEpoller * tcp_epoller;

  public:
    AgentEndTask(TcpEpoller * ptr)
    {
      tcp_epoller = ptr;
    }
    ~AgentEndTask();

    virtual void run();

};

#endif
