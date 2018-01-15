#ifndef _EPOLLER_H_
#define _EPOLLER_H_

class Epoller{
    private:
        int id_;//每个epoller的标志
        int fd_;

    public:
        Epoller(int idd,int fdd);
        ~Epoller();

        int getFd();

        virtual void in() = 0;
        virtual void out() = 0;
};

#endif
