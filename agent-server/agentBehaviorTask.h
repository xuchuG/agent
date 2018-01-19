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

  protected:
    AgentTransManage & agent_trans_manage;
  public:
    AgentBehaviorTask(AgentTransManage & atrans_manage):
        agent_trans_manage(atrans_manage){}
    ~AgentBehaviorTask(){}

    static struct head decodePacHead(Queue & queue);

    virtual void run();
};

#endif
