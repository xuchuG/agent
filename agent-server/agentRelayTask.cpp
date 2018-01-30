#include "agentRelayTask.h"
#include "./packet/packet.h"
#include "./communicationModule/epoll/agentServerEpoller.h"
#include "./agentTaskSupervisor.h"

void AgentRelayTask::run()
{
  struct head headTmp;

  struct pacStandardFormat pac_standard_format;
  tcp_epoller->popRecvPac(pac_standard_format);
  headTmp = decodePacHead(pac_standard_format);

  if(headTmp.cmd != PacketCommand::RelayCmd)
  {
    //未发送期待的报文
    char * head;
    char * tail;
    Packet::MakeErrorAck(AckPacCmd::SEQUENCE_ERROR,head,tail);

    free(pac_standard_format.head);

    struct pacStandardFormat pac_tmp;
    pac_tmp.head = head;
    pac_tmp.tail = tail;
    tcp_epoller->pushSendPac(pac_tmp);

    return;
  }

  TcpEpoller * des_relay_trans;
  AgentTransManage& agent_trans_manage = AgentTaskSupervisor::getInstance().getAgentTransManage();
  if((des_relay_trans = agent_trans_manage.find(headTmp.id)) == NULL)
  {
    cerr << "agent_table:can't find id: " << headTmp.id << endl;
    return;
  }

  //将数据包头部id字段改为发送方id
  long long sender_id;
  AgentTransToIdManage& agent_trans_id_manage = AgentTaskSupervisor::getInstance().getAgentTransToIdManage();
  if((sender_id = agent_trans_id_manage.find(tcp_epoller)) == NULL){
    cerr << "AgentTransToManage:can't find TcpEpoller*\n";
    return;
  }
  ((struct head*)pac_standard_format.head)->id = sender_id;

  des_relay_trans->pushSendPac(pac_standard_format);

  //修改状态
  AgentStateManage& agent_state_manage = AgentTaskSupervisor::getInstance().getAgentStateManage();
  AgentState* agent_state;
  if((agent_state = agent_state_manage.find(tcp_epoller)) == NULL){
        cerr << "AgentStateManage:: find error!\n";
  }
  agent_state->setState(State::RELAY);
  return;
}
