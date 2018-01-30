#ifndef _AGENTSERVEREPOLLER_H_
#define _AGENTSERVEREPOLLER_H_

#include "tcpEpoller.h"

using Queue = queue<pair<char*,char*> >;

class AgentServerEpoller : public TcpEpoller{
    public:
        AgentServerEpoller(){}
        ~AgentServerEpoller(){}

        virtual void readBack();

};

#endif
