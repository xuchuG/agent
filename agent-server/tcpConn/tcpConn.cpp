#include "tcpConn.h"

TcpConn::TcpConn(int linkNumm,char * localIpp,short localPortt,char *remoteIpp,short remotePortt,bool ipBindd,bool portBindd,bool nonBlockk,bool naglee,bool reuseAddrr)
{
  linkNum = linkNumm;
  localIp = localIpp;
  localPort = localPortt;
  remoteIp = remoteIpp;
  remotePort = remotePortt;
  ipBind = ipBindd;
  portBind = portBindd;
  nonBlock = nonBlockk;
  nagle = naglee;
  reuseAddr = reuseAddrr;
}

TcpConn::~TcpConn()
{

}

void TcpConn::run()
{
  cout << "I am in TcpConn run\n";
}

void TcpConn::setNonBlock(int fd)
{
  int flags;
  if((flags = fcntl(fd,F_GETFL,0)) < 0)
  {
    cerr << "fcntl:F_GETFL error!\n";
    return;
  }  
  if(fcntl(fd,F_SETFL,flags | O_NONBLOCK) < 0)
  {
    cerr << "fcntl:F_SETFL error!\n";
    return;
  }  
}

void TcpConn::setNagle(int fd)
{
  int opt = 1;
  if(setsockopt(fd,IPPROTO_TCP,TCP_NODELAY,(const void *)&opt,sizeof(int)) == -1)
  {
    cerr << "set nagle error!\n";
  }
}

void TcpConn::setReuseAddr(int fd)
{
  int opt = 1;
  if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,(const void *)&opt,sizeof(int)) == -1)
  {
    cerr << "set reuse addr!\n";
  }
}
