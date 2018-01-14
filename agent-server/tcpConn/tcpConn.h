#ifndef _TCPCONN_H_
#define _TCPCONN_H_

#include "cHead.h"
class TcpConn
{
  protected:
   vector<int> sock;//所有套接字集合
   int linkNum;//需要建立的连接数
   char * localIp;//需要绑定ip地址, 若无需要提供默认值传参
   short localPort;//需要绑定的端口地址，若无需要提供默认值传参
   char * remoteIp;//服务器ip
   short remotePort;//服务器端口
   bool ipBind;//本地是否绑定ip
   bool portBind;//本地是否绑定端口
   bool nonBlock;//是否设置非阻塞
   bool nagle;//是否取消nagle算法
   bool reuseAddr; //是否设置地址复用
  public:
    TcpConn(int linkNumm,char * localIpp,short localPortt,char *remoteIpp,short remotePortt,bool ipBindd,bool portBindd,bool nonBlockk,bool naglee,bool reuseAddrr);
    ~TcpConn();
    virtual void run();//对于客户端为connect 对于服务器为listen accecpt
    void setNonBlock(int fd);
    void setNagle(int fd);
    void setReuseAddr(int fd);
};

#endif
