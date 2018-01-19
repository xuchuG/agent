#ifndef _AGENTENDTASK_H_
#define _AGENTENDTASK_H_

#include <queue>

#include "agentBehaviorTask.h"
#include "./communicationModule/epoll/tcpEpoller.h"

using Queue = queue<pair<char*,char*> >;

class AgentEndTask : public AgentBehaviorTask
{
  private:
    Queue & recv_que;
    Queue & send_que;
    TcpEpoller * tcp_epoller;

  public:
    AgentEndTask(AgentTransManage & atrans_manage,Queue & recvque,
        Queue & sendque,TcpEpoller * ptr):AgentBehaviorTask(atrans_manage),recv_que(recvque),send_que(sendque)
    {
      tcp_epoller = ptr;
    }
    ~AgentEndTask();

    virtual void run();

};

#endif
