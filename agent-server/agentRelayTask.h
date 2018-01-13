#ifndef AGENTRELAYTASK_H_
#define AGENTREALYTASK_H_

#include <queue.h>

#include "agentBehaviorTask.h"

using Queue = queue<char *,char *>;

class AgentRelayTask : public AgentBehaviorTask
{
  private:
    Queue & recvQue;
    Queue & sendQue;
    agent_trans * relay_trans;

  public:
    AgentRelayTask(AgentTable & table,Queue & recvque,
        Queue & sendque,agent_trans * ptr):AgentBehaviorTask(table)
    {
      recvQue = recvque;
      sendQue = sendque;
      relay_trans = ptr;
    }

    ~AgentRelayTask(){}

    virtual void run();
}

#endif

