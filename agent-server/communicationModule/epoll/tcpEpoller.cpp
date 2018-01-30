#include "tcpEpoller.h"

#include <iostream>

void TcpEpoller::init(long long id,int fd){
    //初始化Epoller id
    setId(id);
    //初始化Epoller fd
    setFd(fd);

    recv_pac_manage.setFd(fd);
    send_pac_manage.setFd(fd);
    tcp_epoller_call_back = std::bind(&TcpEpoller::readBack,this);
}

void TcpEpoller::in(){
    struct pacStandardFormat pac_standard_format;

    if(recv_pac_manage.recvPac(pac_standard_format) == 0){//整包接收完
        pushRecvPac(pac_standard_format);
        tcp_epoller_call_back(this);
    }

}

void TcpEpoller::out(){
    struct pacStandardFormat pac_standard_format;
    if(pac_send_over == 0){
        if(popSendPac(pac_standard_format) < 0){
            return;
        }
    }

    pac_send_over = send_pac_manage.sendPac(pac_standard_format);

}

int TcpEpoller::popRecvPac(struct pacStandardFormat& pac_standard_format){
    std::lock_guard<std::mutex> guard(recv_mutex_);
    if(recv_que.empty()){
        return -1;
    }

    pair<char*,char*> pac = recv_que.front();
    recv_que.pop();
    pac_standard_format.head = pac.first;
    pac_standard_format.tail = pac.second;

    return 0;
}

void TcpEpoller::pushRecvPac(struct pacStandardFormat pac_standard_format){
    std::lock_guard<std::mutex> guard(recv_mutex_);
    recv_que.push(make_pair(pac_standard_format.head,pac_standard_format.tail));
}

int TcpEpoller::popSendPac(struct pacStandardFormat& pac_standard_format){
    std::lock_guard<std::mutex> guard(send_mutex_);
    if(send_que.empty()){
        return -1;
    }

    pair<char*,char*> pac = send_que.front();
    send_que.pop();
    pac_standard_format.head = pac.first;
    pac_standard_format.tail = pac.second;

    return 0;
}

void TcpEpoller::pushSendPac(struct pacStandardFormat pac_standard_format){
    std::lock_guard<std::mutex> guard(send_mutex_);
    send_que.push(make_pair(pac_standard_format.head,pac_standard_format.tail));
}
