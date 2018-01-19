#ifndef _CONNECT_H_
#define _CONNECT_H_

#include "tcpConn.h"
#include <vector>
using namespace std;

class Connect : public TcpConn
{
  public:
      Connect(int linkNumm,char * localIpp,char * remoteIpp,short remotePortt,bool ipBindd,bool portBindd,bool nonBlockk,bool naglee,bool reuseAddrr):
        TcpConn(linkNumm,localIpp,0,remoteIpp,remotePortt,ipBindd,portBindd,nonBlockk,naglee,reuseAddrr){}
      Connect():
        TcpConn(0,"127.0.0.1",0,"127.0.0.1",0,false,false,false,false,false){}

      ~Connect();
      void run();
      vector<int> & getSock();
      
      void operator=(Connect& conn);
};

#endif
