#ifndef _AGENTSTATE_H_
#define _AGENTSTATE_H_

class AgentState
{
    private:
        int state;

    public:
        AgentState(int statee);
        ~AgentState();

        int getState();
        void setState(int statee);
};

namespace State
{
    const int LOGIN = 0;
    const int QUERY = 1;
    const int RELAY = 2;
    const int END = 3;
};

#endif

