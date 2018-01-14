#ifndef _AGENTSTATEMANAGE_H_
#define _AGENTSTATEMANAGE_H_

#include "tableManage.h"

class AgentStateManage : public TableManage<long long,AgentState *>
{
    public:
        AgentStateManage();
};

#endif
