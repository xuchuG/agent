#include "../communicationModule/epoll/supervisor.h"
#include "../communicationModule/tcpConn/tcpServerConn.h"
#include "../task/agentTaskFactory.h"
#include "../communicationModule/epoll/tcpEpoller.h"
#include "../communicationModule/epoll/agentServerEpoller.h"
#include "../threadPool/threadPoolSurpervisor.h"
#include "../threadPool/threadPool.h"
#include <queue>
using namespace std;
using Queue = queue<pair<char*,char*> >;

#define THREADNUM 8

ThreadPoolSurpervisor* g_thread_pool_surpervisor;

ThreadPool thread_pool(THREADNUM);

int main(int argc,char* argv[]){
    Supervisor supervisor;
    supervisor.addListenEpoller<AgentServerEpoller>(TcpServerConn::tcpListen((char *)"192.168.56.101",9899));

    //线程池
    thread_pool.start();

    supervisor.run();

    return 0;
}
