#ifndef _LISTENEPOLLER_H_
#define _LISTENEPOLLER_H_

#include <functional>
#include "epoller.h"

class ListenEpoller : public Epoller{
    private:
        std::function<void(int)> new_connection_callback_;

    public:
        ListenEpoller(int idd,int fdd,std::function<void(int)> call_back):
            Epoller(idd,fdd){
                new_connection_callback_ = call_back;
                }

        ~ListenEpoller(){}

        virtual void in();
        virtual void out();
};

#endif
