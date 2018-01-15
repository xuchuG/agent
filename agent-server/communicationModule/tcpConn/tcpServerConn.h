#ifndef _TCPSERVERCONN_H_
#define _TCPSERVERCONN_H_

#include "tcpConn.h"
class TcpServerConn : public TcpConn
{
  public:
    static int tcpListen(char ip[],short port);
    static int tcpAccept(int listen_socket);
};

#endif
