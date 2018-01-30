#include "agentEndTask.h"
#include "agentBehaviorTask.h"
#include "../packet/packet.h"

void AgentEndTask::run()
{
    struct head headTmp;

    struct pacStandardFormat pac_standard_format;
    tcp_epoller->popRecvPac(pac_standard_format);
    headTmp = AgentBehaviorTask::decodePacHead(pac_standard_format);
    if(headTmp.cmd != PacketCommand::EndCmd)
    {

    }
}
