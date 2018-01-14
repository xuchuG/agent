#ifndef AGENTLOGINTASK_H_
#define AGENTLOGINTASK_H_

#include <queue>

#include "agentBehaviorTask.h"

using Queue = queue<pair<char*,char*> >;

class AgentLoginTask : public AgentBehaviorTask
{
  private:
    Queue & recvQue;//接收缓冲队列
    Queue & sendQue;//发送缓冲队列
    agent_trans * relay_trans;//通信模块

  public:
    AgentLoginTask(AgentTransManage & atrans_manage,Queue & recvque,Queue & sendque,agent_trans * ptr):
      AgentBehaviorTask(atrans_manage),recvQue(recvque),sendQue(sendque)
    {
      relay_trans = ptr;
    }
    ~AgentLoginTask(){}

    virtual void run();

};

#endif
