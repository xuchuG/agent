#ifndef AGENTLOGINTASK_H_
#define AGENTLOGINTASK_H_

#include <queue>

#include "agentBehaviorTask.h"
#include "./communicationModule/epoll/tcpEpoller.h"
#include "./tableManage/agentState.h"
#include "./tableManage/agentTransToIdManage.h"

using Queue = queue<pair<char*,char*> >;

class AgentLoginTask : public AgentBehaviorTask
{
  private:
    AgentTransToIdManage& agent_trans_id_manage;
    AgentState*& agent_state;
    Queue & recv_que;//接收缓冲队列
    Queue & send_que;//发送缓冲队列
    TcpEpoller * tcp_epoller;//通信模块

  public:
    AgentLoginTask(AgentTransManage & atrans_manage,AgentTransToIdManage& agent_trans_id_managee,AgentState*& agent_statee,Queue & recvque,Queue & sendque,TcpEpoller * ptr):
      AgentBehaviorTask(atrans_manage),agent_trans_id_manage(agent_trans_id_managee),agent_state(agent_statee),recv_que(recvque),send_que(sendque)
    {
      tcp_epoller = ptr;
    }
    ~AgentLoginTask(){}

    virtual void run();

};

#endif
