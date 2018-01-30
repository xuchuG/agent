#include "agentBehaviorTask.h"

void AgentBehaviorTask::run()
{

}

struct head AgentBehaviorTask::decodePacHead(struct pacStandardFormat pac)
{
    struct head headTmp;
    char * pac_head;
    pac_head = pac.head;
    headTmp.len = *(int *)pac_head;
    headTmp.cmd = *(int *)(pac_head+4);
    headTmp.id = *(long long *)(pac_head+8);
    return headTmp;
}
