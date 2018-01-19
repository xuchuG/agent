#include "./communicationModule/epoll/supervisor.h"
#include "./communicationModule/tcpConn/tcpServerConn.h"
#include "agentTaskFactory.h"
#include "./communicationModule/epoll/tcpEpoller.h"
#include <queue>
using namespace std;
using Queue = queue<pair<char*,char*> >;

int main(int argc,char* argv[]){
    Supervisor supervisor;
    supervisor.addListenEpoller(TcpServerConn::tcpListen((char *)"192.168.56.101",9899));

    supervisor.addTcpEpollerCallBack([=](Queue& recv_que,Queue& send_que,TcpEpoller* tcp_epoller){
        AgentTaskFactory agent_task_factory;
        agent_task_factory.taskDispatch(recv_que,send_que,tcp_epoller);
    });
    supervisor.run();

    return 0;
}
