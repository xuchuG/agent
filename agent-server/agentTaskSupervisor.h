#ifndef _AGENTTASKSUPERVISOR_H_
#define _AGENTTASKSUPERVISOR_H_

#include "./tableManage/agentStateManage.h"
#include "./tableManage/agentTransManage.h"
#include "./tableManage/agentTransToIdManage.h"

class AgentTaskSupervisor{
    private:
        AgentStateManage agent_state_manage;
        AgentTransManage agent_trans_manage;
        AgentTransToIdManage agent_trans_id_manage;

    private:
        AgentTaskSupervisor(){}
        AgentTaskSupervisor(AgentTaskSupervisor &){}
        AgentTaskSupervisor& operator=(AgentTaskSupervisor const &){}

    public:
        ~AgentTaskSupervisor(){}

        static AgentTaskSupervisor& getInstance();

        AgentStateManage& getAgentStateManage();
        AgentTransManage& getAgentTransManage();
        AgentTransToIdManage& getAgentTransToIdManage();
};

#endif
