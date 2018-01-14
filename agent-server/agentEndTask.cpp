#include "agentEndTask.h"
#include "agentBehaviorTask.h"
#include "./packet/packet.h"

void AgentEndTask::run()
{
    struct head headTmp;

    headTmp = AgentBehaviorTask::decodePacHead(recvQue);
    if(headTmp.cmd != PacketCommand::EndCmd)
    {

    }
}
