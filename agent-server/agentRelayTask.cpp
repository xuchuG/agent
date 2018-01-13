#include "agentRelayTask.h"

virtual void AgentRelayTask::run()
{
  struct head headTmp;
  
  headTmp = AgentBehaviorTask::decodePacHead(recvQue);
  if(headTmp.cmd != Packet::RelayCmd)
  {
    //未发送期待的报文
    char * head;
    char * tail;
    Packet::MakeErrorAck(AckPacState::SEQUENCE_ERROR,head,tail);
    sendQue.push(make_pair(head,tail));
    return;
  }  

  agent_trans * des_relay_trans;
  if((des_relay_trans = agent_table.find(headTmp.id)) < 0)
  {
    cerr << "agent_table:can't find id: " << headTmp.id << endl;
    return;
  }
  
  char * head;
  char * tail;
  head = recvQue.front().first;
  tail = recvQue.front().second;
  recvQue.pop();

  des_relay_trans.sendQue.push(make_pair(head,tail));
  return;
}
