#include "agentLoginTask.h"
#include "../packet/packet.h"
#include "./agentTaskSupervisor.h"

void AgentLoginTask::run()
{
  struct head headTmp;

  struct pacStandardFormat pac_standard_format;
  tcp_epoller->popRecvPac(pac_standard_format);
  headTmp = decodePacHead(pac_standard_format);

  free(pac_standard_format.head);

  if(headTmp.cmd != PacketCommand::LoginCmd)
  {
    //回应客户端未发送登录报文，发送了其他类型的报文
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
  if(agent_trans_manage.isContainsId(headTmp.id))
  {
    //回应客户端登录错误，存在相同的ID的用户在线
    char * head;
    char * tail;
    Packet::MakeErrorAck(AckPacCmd::ID_ALREADY_EXIST,head,tail);

    struct pacStandardFormat pac_tmp;
    pac_tmp.head = head;
    pac_tmp.tail = tail;
    tcp_epoller->pushSendPac(pac_tmp);

    return;
  }

  //将需要登录的的用户id和TcpEpoller*插入表中
  if(agent_trans_manage.insert(headTmp.id,tcp_epoller) < 0)
  {
    //插入id出错
    cerr << "agent_trans_manage:insert id: " <<
    headTmp.id << "error!" << endl;
  }

  AgentTransToIdManage& agent_trans_id_manage = AgentTaskSupervisor::getInstance().getAgentTransToIdManage();
  if(agent_trans_id_manage.insert(tcp_epoller,headTmp.id) < 0)
  {
    //插入id出错
    cerr << "agent_trans_id_manage:insert id: " <<
    headTmp.id << "error!" << endl;
  }

  //回应登录成功
  char * head;
  char * tail;
  Packet::MakeSucAck(AckPacCmd::LOGIN_SUC,head,tail);

  struct pacStandardFormat pac_tmp;
  pac_tmp.head = head;
  pac_tmp.tail = tail;
  tcp_epoller->pushSendPac(pac_tmp);

  //修改状态
  AgentStateManage& agent_state_manage = AgentTaskSupervisor::getInstance().getAgentStateManage();
  AgentState* agent_state;
  if((agent_state = agent_state_manage.find(tcp_epoller)) == NULL){
        cerr << "AgentStateManage:: find error!\n";
  }
  agent_state->setState(State::QUERY);

  return;
}
