#ifndef _RECVPACMANAGE_H_
#define _RECVPACMANAGE_H_

#include "../../packet/packet.h"

#include <queue>
using namespace std;


enum BehaviorState : const int{
    HEADER,
    DATA
};

class RecvPacManage{
    private:
        int fd_;
        char * pac;
        int in_index;
        BehaviorState read_state;

    public:
        RecvPacManage();
        ~RecvPacManage(){}

        void setFd(int fd);

        int recvPac(struct pacStandardFormat& pac_standard_format);
};

#endif
