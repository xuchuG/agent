#include "threadPool.h"
#include <unistd.h>
#include <iostream>
#include "../task/agentBaseTask.h"

void threadItem(AgentBaseTask* task);

ThreadPool::ThreadPool(int thread_num){
    thread_num_ = thread_num;
    thread_work_func_ = NULL;

    {
        int fd[2];
        if( pipe(fd) != 0){
            std::cerr << "ThreadPool:: pipe error!\n";
        }
        read_handler_ = fd[0];
        write_handler_ = fd[1];
    }
}

/*void ThreadPool::threadWork(){   //管道实现
    int count;
    while(1){
        if((count = read(read_handler_,&thread_work_func_,
                        sizeof(std::function<void(void)>)))< 0){
            std::cerr << "ThreadPool:: read pipe error!\n";
        }
        else if(count == 0){
            break;
        }

        thread_work_func_();

    }
}*/

void ThreadPool::append(std::function<void()> task){
    std::lock_guard<std::mutex> guard(mutex_);
    tasks_.push(task);
    condition_empty_.notify_one();
    return;
}

void ThreadPool::threadWork(){
    while(1){
        std::lock_guard<std::mutex> guard(mutex_);
        if(tasks_.empty()){
            condition_empty_.wait(mutex_);
        }

        if(!tasks_.empty()){
            thread_work_func_ = tasks_.front();
            tasks_.pop();
        }
        else{
            continue;
        }

        thread_work_func_();
    }
}

void ThreadPool::start(){
    for(int i=0; i<thread_num_ ; i++){
        thread_vector_.push_back(std::make_shared<std::thread>
                (&ThreadPool::threadWork,this));
    }
}

void ThreadPool::stop(){
    for(auto t : thread_vector_){
        t->join();
    }
}
