#include "./agentTaskFactory.h"
#include "agentBaseTask.h"
#include "agentLoginTask.h"
#include "agentQueryTask.h"
#include "agentRelayTask.h"
#include "agentEndTask.h"
#include "./tableManage/agentTransManage.h"
#include "agentTrans.h"
#include "agentTaskSupervisor.h"

#include <iostream>
#include <queue>

using namespace std;
using Queue = queue<pair<char*,char*> >;

void AgentTaskFactory::taskDispatch(Queue& recv_que,Queue& send_que,TcpEpoller* tcp_epoller)
{
    AgentBaseTask * task = NULL;

    AgentStateManage& agent_state_manage = AgentTaskSupervisor::getInstance().getAgentStateManage();
    AgentTransManage& agent_trans_manage = AgentTaskSupervisor::getInstance().getAgentTransManage();
    AgentTransToIdManage& agent_trans_id_manage = AgentTaskSupervisor::getInstance().getAgentTransToIdManage();

    long long user_id = AgentBehaviorTask::decodePacHead(recv_que).id;
    AgentState* agent_state;
    if((agent_state = agent_state_manage.find(user_id)) == NULL){
        agent_state = new AgentState(State::LOGIN);
        agent_state_manage.insert(user_id,agent_state);
    }

    switch(agent_state->getState())
    {
        case State::LOGIN:
            task = new AgentLoginTask(agent_trans_manage,agent_trans_id_manage,agent_state,recv_que,send_que,tcp_epoller);
            break;
        case State::QUERY:
            task = new AgentQueryTask(agent_trans_manage,agent_state,recv_que,send_que,tcp_epoller);
            break;
        case State::RELAY:
            task = new AgentRelayTask(agent_trans_manage,agent_trans_id_manage,agent_state,recv_que,send_que,tcp_epoller);
            break;
        case State::END:
            //task = new AgentEndTask(a,b,c,d);
            break;
        default:
            cerr << "AgentTaskFactory:未定义的报文类型！\n";
            return;
    }

    task->run();

    delete(task);
}
