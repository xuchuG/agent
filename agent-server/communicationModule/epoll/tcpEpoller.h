#ifndef _TCPEPOLLER_H_
#define _TCPEPOLLER_H_

#include "epoller.h"

class TcpEpoller : public Epoller{
    public:
        TcpEpoller(int id,int fd):
            Epoller(id,fd){}
        ~TcpEpoller();
};

#endif
