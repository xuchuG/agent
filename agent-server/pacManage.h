#ifndef _PACMANAGE_H_
#define _PACMANAGE_H_

#include <string.h>

class Epoll;
class Sesion;

#define  HeadSize 16
#define  HeadLenSize 4
#define  LenAndCmd 8
#define  AckPacSize 12

//ack
#define AckCmd 0 //login ack
#define AckAddFriendCmd 1//add friend ack

//标识该操作是否成功
#define OperSuc 1//成功
#define OperFal 0//失败

//回应登录报文
struct ackLoginPac
{
  int len;
  int ackCmd;//回应报文类型
  int stateNo;//状态码 
};
//回应加好友报文
struct ackAddFriendPac
{
  int len;
  int ackCmd;
  int stateNo;  
};


//服务器发送的报文格式，区别与客户端
struct package
{
  int len;
  int ackCmd;
  long long userId;
  char data[];
};

class PacManage
{
  public:
    class SendQueList
    {   
      public:
        SendQueList * nextPac; 
        char sendPac[];

        bool add_Pac(Epoll &ep,PacManage * remotePac,char * recvPac,int len);
        bool send_Que_list(Epoll &ep,PacManage * ownPac);
    };

  public:
    int fd;
    int inIndex;
    int outIndex;
    
    char *recvPac;//接受包的空间

    SendQueList * sendQueList;//发送消息队列
    bool sqlEmpty;//消息队列是否为空

    long long userId;//在数据传输时，需要用它更改报文，标识数据报文是谁发的
    long long friendId;//保存正在通信的好友id,每次有加好友报文发来时，更新
    //但是存在缺陷，当好友下线时，需要及时回馈给客户
    int fdFriend;

    bool pacRecv;//已经收到过包的数据？
    bool dataPacRecv;//已经收到过报文数据部分
    bool pacRecvOver;//整个包接受完？
    bool pacSend;//已经发过包
    bool pacSendOver;//整个包发完

    PacManage(int fdd,int inIndexx,int outIndexx);
    void readSocket(Epoll &ep,Sesion &sesion);
    void writeSocket(Epoll &ep);
    void recv_Pac(Epoll &ep,Sesion & sesion);
    void sendPac(Epoll &ep);
};

#endif
