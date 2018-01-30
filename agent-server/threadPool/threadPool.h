#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <vector>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadPool{
    private:
        int thread_num_;
        std::vector<std::shared_ptr<std::thread> > thread_vector_;
        std::function<void ()> thread_work_func_;

        std::queue<std::function<void()> > tasks_;
        std::mutex mutex_;
        std::condition_variable_any condition_empty_;

        int read_handler_;
        int write_handler_;

    public:
        ThreadPool(int thread_num);

        int getReadHandler(){
            return read_handler_;
        }

        int getWriteHandler(){
            return write_handler_;
        }

        void threadWork();

        void append(std::function<void()> task);

        void start();
        void stop();
};

#endif

