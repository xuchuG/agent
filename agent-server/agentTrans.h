#ifndef _AGENTTRANS_H_
#define _AGENTTRANS_H_

#include <queue>

class AgentTask;

class agent_trans
{
  public:
    int fd;
    queue<pair<char*,char*> > sendQue;
    queue<pair<char*,char*> > recvQue;
    AgentTask * task;
  public:

};

#endif
