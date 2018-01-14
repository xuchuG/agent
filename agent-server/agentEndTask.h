#ifndef _AGENTENDTASK_H_
#define _AGENTENDTASK_H_

#include <queue>

#include "agentBehaviorTask.h"

using Queue = queue<pair<char*,char*> >;

class AgentEndTask : public AgentBehaviorTask
{
  private:
    Queue & recvQue;
    Queue & sendQue;
    agent_trans * relay_trans;

  public:
    AgentEndTask(AgentTransManage & atrans_manage,Queue & recvque,
        Queue & sendque,agent_trans * ptr):AgentBehaviorTask(atrans_manage),recvQue(recvque),sendQue(sendque)
    {
      relay_trans = ptr;
    }
    ~AgentEndTask();

    virtual void run();

};

#endif
