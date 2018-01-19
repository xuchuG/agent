#ifndef AGENTRELAYTASK_H_
#define AGENTREALYTASK_H_

#include <queue>

#include "agentBehaviorTask.h"
#include "./communicationModule/epoll/tcpEpoller.h"
#include "./tableManage/agentTransToIdManage.h"
#include "./tableManage/agentState.h"

using Queue = queue<pair<char *,char *> >;

class AgentRelayTask : public AgentBehaviorTask
{
  private:
    AgentTransToIdManage& agent_trans_id_manage;
    AgentState* agent_state;
    Queue & recv_que;
    Queue & send_que;
    TcpEpoller * tcp_epoller;

  public:
    AgentRelayTask(AgentTransManage& atrans_manage,AgentTransToIdManage& agent_trans_id_managee,AgentState* agent_statee,Queue & recvque,
        Queue & sendque,TcpEpoller * ptr):AgentBehaviorTask(atrans_manage),agent_trans_id_manage(agent_trans_id_managee),
        agent_state(agent_statee),recv_que(recvque),send_que(sendque)
    {
        tcp_epoller = ptr;
    }

    ~AgentRelayTask(){}

    virtual void run();
};

#endif

