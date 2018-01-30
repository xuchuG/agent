#include "agentQueryTask.h"
#include "./packet/packet.h"
#include "./communicationModule/epoll/agentServerEpoller.h"
#include "./agentTaskSupervisor.h"
void AgentQueryTask::run()
{
  struct head headTmp;

  struct pacStandardFormat pac_standard_format;
  tcp_epoller->popRecvPac(pac_standard_format);
  headTmp = decodePacHead(pac_standard_format);

  free(pac_standard_format.head);

  if(headTmp.cmd != PacketCommand::QueryCmd)
  {
    //未发送所期待的查询报文
    char * head;
    char * tail;
    Packet::MakeErrorAck(AckPacCmd::SEQUENCE_ERROR,head,tail);

    struct pacStandardFormat pac_tmp;
    pac_tmp.head = head;
    pac_tmp.tail = tail;
    tcp_epoller->pushSendPac(pac_tmp);

    return;
  }

  AgentTransManage& agent_trans_manage = AgentTaskSupervisor::getInstance().getAgentTransManage();
  if(agent_trans_manage.isContainsId(headTmp.id) < 0)
  {
    //对端还没登录
    char * head;
    char * tail;
    Packet::MakeErrorAck(AckPacCmd::USER_OFFLINE,head,tail);

    struct pacStandardFormat pac_tmp;
    pac_tmp.head = head;
    pac_tmp.tail = tail;
    tcp_epoller->pushSendPac(pac_tmp);

    return;
  }

  //回应查询成功
  char * head;
  char * tail;
  Packet::MakeSucAck(AckPacCmd::QUERY_SUC,head,tail);

  struct pacStandardFormat pac_tmp;
  pac_tmp.head = head;
  pac_tmp.tail = tail;
  tcp_epoller->pushSendPac(pac_tmp);

  //改变状态
  AgentStateManage& agent_state_manage = AgentTaskSupervisor::getInstance().getAgentStateManage();
  AgentState* agent_state;
  if((agent_state = agent_state_manage.find(tcp_epoller)) == NULL){
        cerr << "AgentStateManage:: find error!\n";
  }
  agent_state->setState(State::RELAY);

  return;
}
