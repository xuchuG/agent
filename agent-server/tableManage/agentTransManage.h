#ifndef _AGENTTRANSMANAGE_H_
#define _AGENTTRANSMANAGE_H_

#include "tableManage.h"
#include "../agentTrans.h"

class AgentTransManage : public TableManage<long long,agent_trans *>
{
    public:
        AgentTransManage(){}
};

#endif
