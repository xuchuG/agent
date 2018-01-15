#ifndef _AGENTSERVEREPOLLER_H_
#define _AGENTSERVEREPOLLER_H_

#include "tcpEpoller.h"

class AgentServerEpoller : public TcpEpoller{
    public:
        AgentServerEpoller(int id,int fd):
            TcpEpoller(id,fd){}
        ~AgentServerEpoller(){}
};

#endif
