#include "agentServerEpoller.h"
#include <iostream>
#include "epoll.h"
#include "../../task/agentTaskFactory.h"

using namespace std;

void AgentServerEpoller::readBack(){
    AgentTaskFactory agent_task_factory;
    agent_task_factory.taskDispatch(this);
}
