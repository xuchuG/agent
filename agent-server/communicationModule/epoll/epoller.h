#ifndef _EPOLLER_H_
#define _EPOLLER_H_

class Epoller{
    private:
        long long id_;//每个epoller的标志
        int fd_;

    public:
        Epoller(){}             //for agentServerEpoller
        Epoller(int id,int fd); //for listenEpoller
        ~Epoller(){}

        void setId(long long id);
        long long getId();

        void setFd(int fd);
        int getFd();

        virtual void in() = 0;
        virtual void out() = 0;
};

#endif
