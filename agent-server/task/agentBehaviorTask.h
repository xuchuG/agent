#ifndef _BEHAVIORTASK_H_
#define _BEHAVIORTASK_H_

#include "agentBaseTask.h"
#include "../packet/packet.h"

class AgentBehaviorTask : public AgentBaseTask
{
  private:

  public:
    AgentBehaviorTask(){}
    ~AgentBehaviorTask(){}

    struct head decodePacHead(struct pacStandardFormat pac);

    virtual void run();
};

#endif
