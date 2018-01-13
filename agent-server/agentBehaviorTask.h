#ifndef _BEHAVIORTASK_H_
#define _BEHAVIORTASK_H_

#include "agentBaseTask.h"

class AgentBehaviorTask : public AgentBaseTask
{
  private:

  protected:
    AgentTable & agent_table;
  public:
    AgentBehaviorTask(AgentTable & table);
    ~AgentBehaviorTask(){}

    virtual void run();
}

#endif
