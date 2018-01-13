#ifndef _AGENTTRANS_H_
#define _AGENTTRANS_H_

#include <queue>

class AgentTask;

class AgentTrans
{
  private:
    int fd;
    queue<pair<char*,int> > sendQue;
    queue<pair<char*,int> > recvQue;
    AgentTask * task;
  public:
    struct packet  

}

#endif
