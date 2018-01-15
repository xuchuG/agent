#include "listenEpoller.h"
#include "../tcpConn/tcpServerConn.h"

void in(){
    int fd = TcpServerConn::tcpAccept(getFd());
    new_connection_callback_(fd);
}

void out(){
    cerr << "error! ListenEpoller : call out()\n";
}
