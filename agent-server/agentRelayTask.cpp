#include "agentRelayTask.h"
#include "./packet/packet.h"
#include "./communicationModule/epoll/agentServerEpoller.h"

void AgentRelayTask::run()
{
  struct head headTmp;

  headTmp = AgentBehaviorTask::decodePacHead(recv_que);
  if(headTmp.cmd != PacketCommand::RelayCmd)
  {
    //未发送期待的报文
    char * head;
    char * tail;
    Packet::MakeErrorAck(AckPacCmd::SEQUENCE_ERROR,head,tail);

    free(recv_que.front().first);
    recv_que.pop();
    send_que.push(make_pair(head,tail));
    return;
  }

  TcpEpoller * des_relay_trans;
  if((des_relay_trans = agent_trans_manage.find(headTmp.id)) == NULL)
  {
    cerr << "agent_table:can't find id: " << headTmp.id << endl;
    return;
  }

  char * head;
  char * tail;
  head = recv_que.front().first;
  tail = recv_que.front().second;

  //将数据包头部id字段改为发送方id
  long long sender_id;
  if((sender_id = agent_trans_id_manage.find(tcp_epoller)) == NULL){
    cerr << "AgentTransToManage:can't find TcpEpoller*\n";
    return;
  }
  ((struct head*)head)->id = sender_id;

  recv_que.pop();

  (dynamic_cast<AgentServerEpoller*> (des_relay_trans))->getSendQue().push(make_pair(head,tail));

  //修改状态
  agent_state->setState(State::RELAY);
  return;
}
