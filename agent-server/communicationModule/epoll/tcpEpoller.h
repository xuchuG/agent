#ifndef _TCPEPOLLER_H_
#define _TCPEPOLLER_H_

#include "epoller.h"
#include "../tcpConn/recvPacManage.h"
#include "../tcpConn/sendPacManage.h"
#include "../../packet/packet.h"
#include <queue>
#include <mutex>
#include <functional>

using Queue = std::queue<std::pair<char*,char*> >;

class TcpEpoller : public Epoller{
    protected:
        std::function<void(TcpEpoller*)> tcp_epoller_call_back;

        Queue recv_que;
        Queue send_que;

        std::mutex recv_mutex_;
        std::mutex send_mutex_;

        RecvPacManage recv_pac_manage;
        SendPacManage send_pac_manage;

        int pac_send_over;//标识有没有发完一个包

    public:
        TcpEpoller(){
            pac_send_over = 0;
        }
        ~TcpEpoller(){}

        virtual void init(long long id,int fd);

        virtual void in();
        virtual void out();

        virtual void readBack() = 0;

        int popRecvPac(struct pacStandardFormat& pac_standard_format);
        void pushRecvPac(struct pacStandardFormat pac);

        int popSendPac(struct pacStandardFormat& pac_standard_format);
        void pushSendPac(struct pacStandardFormat pac);
};

#endif
