#include "sendPacManage.h"
#include <unistd.h>
#include <error.h>
#include <string.h>
#include <iostream>
using namespace std;

SendPacManage::SendPacManage(int fdd){
    this->fd = fdd;
    this->pac_head = NULL;
    this->pac_tail = NULL;
    out_index = 0;
}

int SendPacManage::sendPac(Queue& send_que){
    if(out_index == 0){//发送队列取出一个元素
        pair<char*,char*> send_pac = send_que.front();
        this->pac_head = send_pac.first;
        this->pac_tail = send_pac.second;
    }

    int count;
    if((count = write(fd,pac_head+out_index,(pac_tail-pac_head)-out_index)) < 0){
        if((errno != EWOULDBLOCK) && (errno != EINTR)){
            cerr << "write error\n";
            cerr << "errno:" << errno << strerror(errno) << endl;
        }
        else if(errno == EWOULDBLOCK){
            return -1;
        }
    }
    else{
        out_index += count;
    }

    if(out_index == *(int*)(this->pac_head)){
        free(pac_head);
        out_index = 0;

        send_que.pop();
    }

    return 0;
}
