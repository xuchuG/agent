#include "threadPoolSurpervisor.h"
#include <unistd.h>
#include <iostream>

void ThreadPoolSurpervisor::postThreadWork(CALLBACKFUNC thread_work){
    thread_work_queue_.push(thread_work);
}

void ThreadPoolSurpervisor::in(){

}

void ThreadPoolSurpervisor::out(){
    int count;
    while(!thread_work_queue_.empty()){
        if((count = write(getFd(),&thread_work_queue_.front(),
                        sizeof(CALLBACKFUNC))) < 0){
                std::cerr << "ThreadPoolSurpervisor:: write pipe error!\n";
        }
        thread_work_queue_.pop();
    }
}
