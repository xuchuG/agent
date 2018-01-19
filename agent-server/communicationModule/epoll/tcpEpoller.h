#ifndef _TCPEPOLLER_H_
#define _TCPEPOLLER_H_

#include "epoller.h"
#include <functional>
#include <queue>
using Queue = std::queue<std::pair<char*,char*> >;

class TcpEpoller : public Epoller{
    protected:
        std::function<void(Queue&,Queue&,TcpEpoller*)> tcp_epoller_call_back;

    public:
        TcpEpoller(int id,int fd,std::function<void(Queue&,Queue&,TcpEpoller*)> call_back):
            Epoller(id,fd){
                tcp_epoller_call_back = call_back;
            }
        ~TcpEpoller(){}

        virtual void in();
        virtual void out();
};

#endif
