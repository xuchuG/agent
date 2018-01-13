#include "agentLoginTask.h"

virtual void AgentLoginTask::run()
{
  struct head headTmp;
  
  headTmp = AgentBehaviorTask::decodePacHead(recvQue);
  if(headTmp.cmd != Packet::RegisterCmd)
  {
    //回应客户端未发送登录报文，发送了其他类型的报文  
    char * head;
    char * tail;
    Packet::MakeErrorAck(AckPacState::SEQUENCE_ERROR,head,tail);
    sendQue.push(make_pair(head,tail));
    return; 
  }

  if(agent_table.isContainsId(headTmp.id))
  {
    //回应客户端登录错误，存在相同的ID的用户在线
    char * head;
    char * tail;
    Packet::MakeErrorAck(AckPacState::ID_ALREADY_EXIST,head,tail);
    sendQue.push(make_pair(head,tail));
    return;
  }

  //将需要登录的的用户id和agent_trans*插入表中
  if(agent_table.insert(headTmp.id,relay_trans) < 0)
  {
    //插入id出错
    cerr << "agent_table:insert id: " <<
      headTmp.id << "error!" << endl;
  }

  //回应登录成功 
  char * head；
  char * tail;
  Packet::MakeSucAck(AckPacState::LOGIN_SUC,head,tail);
  sendQue.push(make_pair(head,tail));
  return;
}
