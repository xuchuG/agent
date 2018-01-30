#include "listenEpoller.h"
#include "../tcpConn/tcpServerConn.h"
#include <iostream>
using namespace std;

void ListenEpoller::in(){
    int fd = TcpServerConn::tcpAccept(getFd());
    new_connection_callback_(fd);
}

void ListenEpoller::out(){
    cerr << "error! ListenEpoller : call out()\n";
}
