#include "agentQueryTask.h"

virtual void AgentQueryTask::run()
{
  struct head headTmp;

  headTmp = AgentBehavior::decodePacHead(recvQue);
  if(headTmp.cmd == Packet::QueryCmd)
  {
    //未发送所期待的查询报文
    char * head;
    char * tail;
    Packet::MakeErrorAck(AckPacState::SEQUEUE_ERROR,head,tail);
    sendQue.push(make_pair(head,tail));
    return;
  }

  if(agent_table.isContainsId(headTmp.id) < 0)
  {
    //对端还没登录
    char * head;
    char * tail;
    Packet::MakeErrorAck(AckPacState::USER_OFFLINE,head,tail);
    sendQue.push(make_pair(head,tail));
    return;
  }

  //回应查询成功
  char * head;
  char * tail;
  Packet::MakeSucAck(AckPacState::QUERY_SUC,head,tail);
  sendQue.push(make_pair(head,tail));
  return;
}
