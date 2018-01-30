#ifndef _THREADPOOLSURPERVISOR_H_
#define _THREADPOOLSURPERVISOR_H_

#include "../communicationModule/epoll/epoller.h"
#include <functional>
#include <queue>

using namespace std;

using CALLBACKFUNC = std::function<void()>;

class ThreadPoolSurpervisor : public Epoller{
    private:
        queue<CALLBACKFUNC> thread_work_queue_;
    public:
        ThreadPoolSurpervisor(int id,int write_handler):
            Epoller(id,write_handler){}

        void postThreadWork(CALLBACKFUNC thread_work);

        virtual void in();
        virtual void out();

};

#endif
