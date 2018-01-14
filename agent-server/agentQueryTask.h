#ifndef AGENTQUERYTASK_H_
#define AGENTQUERYTASK_H_

#include <queue>

#include "agentBehaviorTask.h"

using Queue = queue<pair<char*,char*> >;

class AgentQueryTask : public AgentBehaviorTask
{
  private:
    Queue & recvQue;
    Queue & sendQue;
    agent_trans * relay_trans;

  public:
    AgentQueryTask(AgentTransManage & atrans_manage,Queue & recvque,
        Queue & sendque,agent_trans * ptr):AgentBehaviorTask(atrans_manage),recvQue(recvque),sendQue(sendque)
    {
      relay_trans = ptr;
    }
    ~AgentQueryTask(){}

    virtual void run();
};


#endif
