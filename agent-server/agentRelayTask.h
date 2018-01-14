#ifndef AGENTRELAYTASK_H_
#define AGENTREALYTASK_H_

#include <queue>

#include "agentBehaviorTask.h"

using Queue = queue<pair<char *,char *> >;

class AgentRelayTask : public AgentBehaviorTask
{
  private:
    Queue & recvQue;
    Queue & sendQue;
    agent_trans * relay_trans;

  public:
    AgentRelayTask(AgentTransManage & atrans_manage,Queue & recvque,
        Queue & sendque,agent_trans * ptr):AgentBehaviorTask(atrans_manage),recvQue(recvque),sendQue(sendque)
    {
      relay_trans = ptr;
    }

    ~AgentRelayTask(){}

    virtual void run();
};

#endif

