#ifndef _BEHAVIORTASK_H_
#define _BEHAVIORTASK_H_

#include "agentBaseTask.h"
#include "./tableManage/agentTransManage.h"
#include "./packet/packet.h"
#include <queue>

using Queue = queue<pair<char*,char*> >;

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
