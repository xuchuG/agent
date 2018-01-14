#include "agentQueryTask.h"
#include "./packet/packet.h"


void AgentQueryTask::run()
{
  struct head headTmp;

  headTmp = AgentBehaviorTask::decodePacHead(recvQue);
  recvQue.pop();

  if(headTmp.cmd != PacketCommand::QueryCmd)
  {
    //未发送所期待的查询报文
    char * head;
    char * tail;
    Packet::MakeErrorAck(AckPacCmd::SEQUENCE_ERROR,head,tail);
    sendQue.push(make_pair(head,tail));
    return;
  }

  if(agent_trans_manage.isContainsId(headTmp.id) < 0)
  {
    //对端还没登录
    char * head;
    char * tail;
    Packet::MakeErrorAck(AckPacCmd::USER_OFFLINE,head,tail);
    sendQue.push(make_pair(head,tail));
    return;
  }

  //回应查询成功
  char * head;
  char * tail;
  Packet::MakeSucAck(AckPacCmd::QUERY_SUC,head,tail);
  sendQue.push(make_pair(head,tail));
  return;
}
