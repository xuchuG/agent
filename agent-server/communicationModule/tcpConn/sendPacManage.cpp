#include "sendPacManage.h"
#include <unistd.h>
#include <error.h>
#include <string.h>
#include <iostream>
using namespace std;

SendPacManage::SendPacManage(){
    this->pac_head = NULL;
    this->pac_tail = NULL;
    out_index = 0;
}

void SendPacManage::setFd(int fd){
    this->fd_ = fd;
}

int SendPacManage::sendPac(struct pacStandardFormat pac_standard_format){ //返回0->发完一个包 -1->未发完一个包
    if(out_index == 0){
        this->pac_head = pac_standard_format.head;
        this->pac_tail = pac_standard_format.tail;
    }

    int count;
    if((count = write(fd_,pac_head+out_index,(pac_tail-pac_head)-out_index)) < 0){
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

        return 0;
    }

    return -1;
}
