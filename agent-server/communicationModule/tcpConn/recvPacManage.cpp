#include "recvPacManage.h"
#include "../../packet/packet.h"
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>
#include <iostream>

RecvPacManage::RecvPacManage(int fdd){
    fd = fdd;
    pac = (char*)malloc(HeadSize);
    in_index = 0;
    read_state = BehaviorState::HEADER;
}

int RecvPacManage::recvPac(Queue& recv_que){//return 0-->接收完一个包  return -1---->未接收完一个包
    int count;
    switch(read_state){
        case BehaviorState::HEADER:
            if((count = read(fd,pac+in_index,HeadSize-in_index)) < 0){
                if((errno != EWOULDBLOCK) && (errno != EINTR)){
                    cerr << "read error!\n";
                    cerr << "errno: " << errno << "  " << strerror(errno) << endl;
                }
            }
            else if(count == 0){//客户端退出

            }
            else{
                in_index += count;
            }
            if(in_index == HeadSize){
                int pac_len = *((int*)pac);
                if(pac_len == HeadSize){
                    //加入到接收队列
                    recv_que.push(make_pair(pac,pac+pac_len));
                    pac = (char *)malloc(HeadSize);
                    in_index = 0;
                    read_state = BehaviorState::HEADER;
                    return 0;
                }
                else if(pac_len > HeadSize){
                    if((pac = (char*)realloc(pac,pac_len)) == NULL){
                        cerr << "realloc memory error!\n";
                    }

                    read_state = BehaviorState::DATA;
                }
            }
            break;

        case BehaviorState::DATA:
            int pac_len = *((int*)pac);
            if((count = read(fd,pac+in_index,pac_len-in_index)) < 0){
                if((errno != EWOULDBLOCK) && (errno != EINTR)){
                    cerr << "read error!\n";
                    cerr << "errno: " << errno << endl;
                }
            }
            else{
                in_index += count;
            }

            if(in_index == pac_len){
                //放到接收队列
                recv_que.push(make_pair(pac,pac+pac_len));
                pac = (char *)malloc(HeadSize);
                in_index = 0;
                read_state = BehaviorState::HEADER;
                return 0;
            }
    }

    return -1;
}
