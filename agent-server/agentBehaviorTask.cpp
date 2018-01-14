#include "agentBehaviorTask.h"

void AgentBehaviorTask::run()
{

}

struct head AgentBehaviorTask::decodePacHead(Queue & queue)
{
    struct head headTmp;
    char * pac;
    pair<char*,char*> tmp = queue.front();
    pac = tmp.first;
    headTmp.len = *(int *)pac;
    headTmp.cmd = *(int *)(pac+4);
    headTmp.id = *(long long *)(pac+8);
    return headTmp;
}
