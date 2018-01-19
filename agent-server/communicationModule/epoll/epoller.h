#ifndef _EPOLLER_H_
#define _EPOLLER_H_

class Epoller{
    private:
        long long id_;//每个epoller的标志
        int fd_;

    public:
        Epoller(long long idd,int fdd);
        ~Epoller(){}

        long long getId();
        int getFd();

        virtual void in() = 0;
        virtual void out() = 0;
};

#endif
