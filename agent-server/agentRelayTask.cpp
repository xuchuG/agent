#include "agentRelayTask.h"
#include "./packet/packet.h"

void AgentRelayTask::run()
{
  struct head headTmp;

  headTmp = AgentBehaviorTask::decodePacHead(recvQue);
  if(headTmp.cmd != PacketCommand::RelayCmd)
  {
    //未发送期待的报文
    char * head;
    char * tail;
    Packet::MakeErrorAck(AckPacCmd::SEQUENCE_ERROR,head,tail);
    sendQue.push(make_pair(head,tail));
    return;
  }

  agent_trans * des_relay_trans;
  if((des_relay_trans = agent_trans_manage.find(headTmp.id)) < 0)
  {
    cerr << "agent_table:can't find id: " << headTmp.id << endl;
    return;
  }

  char * head;
  char * tail;
  head = recvQue.front().first;
  tail = recvQue.front().second;
  recvQue.pop();

  des_relay_trans->sendQue.push(make_pair(head,tail));
  return;
}
