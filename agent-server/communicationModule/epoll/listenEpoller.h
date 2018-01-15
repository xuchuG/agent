#ifndef _LISTENEPOLLER_H_
#define _LISTENEPOLLER_H_

#include <functional>

class ListenEpoller : public Epoller{
    private:
        std::function<void(int)> new_connection_callback_;

    public:
        ListenEpoller(int idd,int fdd):
            Epoller(idd,fdd){}
        ~ListenEpoller(){}

};

#endif
