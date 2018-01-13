#ifndef _AGENTENDTASK_H_
#define _AGENTENDTASK_H_

#include <queue.h>

#include "agentBehaviorTask.h"

using Queue = queue<char*,char*>;

class AgentEndTask : public AgentBehaviorTask
{
  private:
    Queue & recvQue;
    Queue & sendQue;
    agent_trans * relay_trans;   

  public:
    AgentEndTask(AgentTable & table,Queue & recvque,
        Queue & sendque,agent_trans * ptr):AgentBehaviorTask(table)
    {
      recvQue = recvque;
      sendQue = sendque;
      relay_trans = ptr;
    }
    ~AgentEndTask();

    virtual void run();

} 

#endif
