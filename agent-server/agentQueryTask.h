#ifndef AGENTQUERYTASK_H_
#define AGENTQUERYTASK_H_

#include <queue.h>

#include "agentBehaviorTask.h"

using Queue = queue<char*,char*>;

class AgentQueryTask : public AgentBehavior
{
  private:
    Queue & recvQue;
    Queue & sendQue;
    agent_trans * relay_trans;

  public:
    AgentQueryTask(AgentTable & agent_table,Queue & recvque,
        Queue & sendque,agent_trans * ptr):AgentTable(agent_table)
    {
      recvQue = recvque;
      sendQue = sendque;
      relay_trans = ptr;
    }
    ~AgentQueryTask(){}

    virtual void run();
}


#endif
