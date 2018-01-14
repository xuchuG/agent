#ifndef _CONNECT_H_
#define _CONNECT_H_

#include "tcpConn.h"
class Listen : public TcpConn
{
  private:
    int listenSocket;
  public:
      Listen(char * localIpp,short localPortt,bool ipBindd,bool portBindd,bool nonBlockk,bool naglee,bool reuseAddrr):
        TcpConn(0,localIpp,localPortt,(char *)"127.0.0.1",0,ipBindd,portBindd,nonBlockk,naglee,reuseAddrr){}
      ~Listen();
      int run();//return the accept socket
      void listenSer();
      int getListenSocket();
};

#endif
