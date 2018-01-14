#include "agentTaskFactory.h"
#include "./tableManage/agentState.h"


int main()
{
    AgentTaskFactory a;
    a.taskDispatch(*(new AgentState(State::LOGIN)));
}
