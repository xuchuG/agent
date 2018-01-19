#ifndef AGENTQUERYTASK_H_
#define AGENTQUERYTASK_H_

#include <queue>

#include "agentBehaviorTask.h"
#include "./communicationModule/epoll/tcpEpoller.h"
#include "./tableManage/agentState.h"

using Queue = queue<pair<char*,char*> >;

class AgentQueryTask : public AgentBehaviorTask
{
  private:
    AgentState* agent_state;
    Queue & recv_que;
    Queue & send_que;
    TcpEpoller * tcp_epoller;

  public:
    AgentQueryTask(AgentTransManage & atrans_manage,AgentState* agent_statee,Queue & recvque,
        Queue & sendque,TcpEpoller * ptr):AgentBehaviorTask(atrans_manage),agent_state(agent_statee),recv_que(recvque),send_que(sendque)
    {
      tcp_epoller = ptr;
    }
    ~AgentQueryTask(){}

    virtual void run();
};


#endif
