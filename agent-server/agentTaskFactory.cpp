#include "./agentTaskFactory.h"
#include "agentBaseTask.h"
#include "agentLoginTask.h"
#include "agentQueryTask.h"
#include "agentRelayTask.h"
#include "agentEndTask.h"
#include "./tableManage/agentTransManage.h"
#include "agentTrans.h"

#include <iostream>
#include <queue>

using namespace std;
using Queue = queue<pair<char*,char*> >;

void AgentTaskFactory::taskDispatch(AgentState &agent_state)
{
    AgentBaseTask * task = NULL;

    /********/
    AgentTransManage a;
    Queue b;
    Queue c;
    agent_trans* d;
    /*******/

    switch(agent_state.getState())
    {
        case State::LOGIN:
            task = new AgentLoginTask(a,b,c,d);
            break;
        case State::QUERY:
            task = new AgentQueryTask(a,b,c,d);
            break;
        case State::READ:
            task = new AgentRelayTask(a,b,c,d);
        case State::WRITE:
            task = new AgentRelayTask(a,b,c,d);
            agent_state.setState(State::READ);
            break;
        case State::END:
            //task = new AgentEndTask(a,b,c,d);
            break;
        default:
            cerr << "AgentTaskFactory:未定义的报文类型！\n";
    }

    task->run();
}
