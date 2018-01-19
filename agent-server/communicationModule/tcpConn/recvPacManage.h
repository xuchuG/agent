#ifndef _RECVPACMANAGE_H_
#define _RECVPACMANAGE_H_

#include <queue>
using namespace std;

using Queue = queue<pair<char*,char*> >;

enum BehaviorState : const int{
    HEADER,
    DATA
};

class RecvPacManage{
    private:
        int fd;
        char * pac;
        int in_index;
        BehaviorState read_state;

    public:
        RecvPacManage(int fdd);

        int recvPac(Queue& recv_que);
};

#endif
