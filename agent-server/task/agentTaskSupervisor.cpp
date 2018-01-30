#include "agentTaskSupervisor.h"

AgentTaskSupervisor& AgentTaskSupervisor::getInstance(){
    static AgentTaskSupervisor agent_task_supervisor;
    return agent_task_supervisor;
}

AgentStateManage& AgentTaskSupervisor::getAgentStateManage(){
    return agent_state_manage;
}

AgentTransManage& AgentTaskSupervisor::getAgentTransManage(){
    return agent_trans_manage;
}

AgentTransToIdManage& AgentTaskSupervisor::getAgentTransToIdManage(){
    return agent_trans_id_manage;
}
