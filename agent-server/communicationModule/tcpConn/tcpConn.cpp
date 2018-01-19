#include "tcpConn.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <iostream>
using namespace std;

void TcpConn::setNonBlock(int fd){
    int flags;
    if((flags = fcntl(fd,F_GETFL,0)) < 0){
        cerr << "fcntl:F_GETFL error!\n";
        return;
    }

    if(fcntl(fd,F_SETFL,flags | O_NONBLOCK) < 0){
        cerr << "fcntl:F_SETFL error!\n";
        return;
    }
}

void TcpConn::setNagle(int fd){
    int opt = 1;
    if(setsockopt(fd,IPPROTO_TCP,TCP_NODELAY,
            (const void *)&opt,sizeof(int)) == -1){
        cerr << "set nagle error!\n";
  }
}

void TcpConn::setReuseAddr(int fd){
    int opt = 1;
    if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,
            (const void *)&opt,sizeof(int)) == -1){
        cerr << "set reuse addr error!\n";
  }
}
