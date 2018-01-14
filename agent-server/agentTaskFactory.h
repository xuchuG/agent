#ifndef _AGENTTASKFACTORY_H_
#define _AGENTTASKFACTORY_H_

#include "./tableManage/agentState.h"

class AgentTaskFactory
{
    public:
        void taskDispatch(AgentState &agent_state);
};

#endif

