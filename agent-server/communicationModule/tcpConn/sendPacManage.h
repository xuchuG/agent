#ifndef _SENDPACMANAGE_H_
#define _SENDPACMANAGE_H_

#include "../../packet/packet.h"

#include <queue>

class SendPacManage{
    private:
        int fd_;
        char* pac_head;
        char* pac_tail;
        int out_index;

    public:
        SendPacManage();
        ~SendPacManage(){}

        void setFd(int fd);

        int sendPac(struct pacStandardFormat pac_standard_format);
};

#endif
