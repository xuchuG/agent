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
    const int READ = 2;
    const int WRITE = 3;
    const int END = 4;
};

#endif

