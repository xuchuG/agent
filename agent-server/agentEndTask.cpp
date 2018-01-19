#include "agentEndTask.h"
#include "agentBehaviorTask.h"
#include "./packet/packet.h"

void AgentEndTask::run()
{
    struct head headTmp;

    headTmp = AgentBehaviorTask::decodePacHead(recv_que);
    if(headTmp.cmd != PacketCommand::EndCmd)
    {

    }
}
