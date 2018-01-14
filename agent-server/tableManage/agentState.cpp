#include "agentState.h"

AgentState::AgentState(int statee)
{
    state = statee;
}

AgentState::~AgentState()
{

}

int AgentState::getState()
{
    return state;
}

void AgentState::setState(int statee)
{
    state = statee;
}
