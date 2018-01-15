#ifndef _TCPCONN_H_
#define _TCPCONN_H_

class TcpConn{
  public:
    static void setNonBlock(int fd);
    static void setNagle(int fd);
    static void setReuseAddr(int fd);
};

#endif
