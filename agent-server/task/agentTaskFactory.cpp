#include "./agentTaskFactory.h"
#include "agentBaseTask.h"
#include "agentLoginTask.h"
#include "agentQueryTask.h"
#include "agentRelayTask.h"
#include "agentEndTask.h"
#include "../tableManage/agentTransManage.h"
#include "agentTaskSupervisor.h"
#include "../threadPool/threadPoolSurpervisor.h"
#include "../threadPool/threadPool.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

extern ThreadPoolSurpervisor* g_thread_pool_surpervisor;

extern ThreadPool thread_pool;

void threadItem(AgentBaseTask* task){
    task->run();
}


void AgentTaskFactory::taskDispatch(TcpEpoller* tcp_epoller)
{
    AgentBaseTask *task = NULL;

    //long long user_id = AgentBehaviorTask::decodePacHead(recv_que).id;
    AgentState* agent_state;
    AgentStateManage& agent_state_manage = AgentTaskSupervisor::getInstance().getAgentStateManage();
    if((agent_state = agent_state_manage.find(tcp_epoller)) == NULL){
        agent_state = new AgentState(State::LOGIN);
        agent_state_manage.insert(tcp_epoller,agent_state);
    }


    switch(agent_state->getState())
    {
        case State::LOGIN:
            task = new AgentLoginTask(tcp_epoller);
            break;
        case State::QUERY:
            task = new AgentQueryTask(tcp_epoller);
            break;
        case State::RELAY:
            task = new AgentRelayTask(tcp_epoller);
            break;
        case State::END:
            //task = new AgentEndTask(a,b,c,d);
            break;
        default:
            cerr << "AgentTaskFactory:未定义的报文类型！\n";
            return;
    }

    /*g_thread_pool_surpervisor->postThreadWork([(*task)]()
            {
                task->run();
            });*/

    thread_pool.append([task](){
                task->run();
            });

    //std::function<void()>  work = std::bind(threadItem,task);
    //g_thread_pool_surpervisor->postThreadWork(work);

    return;
    //回调时处理
    //delete(task);
}
