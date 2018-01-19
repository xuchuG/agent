#ifndef _SENDPACMANAGE_H_
#define _SENDPACMANAGE_H_

#include <queue>
using Queue = std::queue<std::pair<char*,char*> >;

class SendPacManage{
    private:
        int fd;
        char* pac_head;
        char* pac_tail;
        int out_index;

    public:
        SendPacManage(int fdd);

        int sendPac(Queue& send_que);
};

#endif
