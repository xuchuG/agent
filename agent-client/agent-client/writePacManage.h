#ifndef _WRITEPACMANAGE_H_
#define _WRITEPACMANAGE_H_

#include "epoll.h"
#include "fileOp.h"
#include <string.h>
#include "readPacManage.h"

//cmd命令规范
#define LoginCmd 0
#define AddFriendCmd 1
#define ToFriendCmd 2
#define AddGroupCmd 3
#define ToGroupCmd 4

//各种包的大小
#define LenAndCmd 8
#define HeadLenSize 4
#define HeadSize 16
#define AckStateSize 16

struct loginPac
{
  int len;//包括头部的总长度
  int cmd;//登录命令
  long long userId;//用户标识
};

struct addFriendPac
{
  int len;
  int cmd;
  long long friendId;//好友id
};

struct  toFriendPac
{
  int len ;
  int cmd;
  long long friendId;
  char data[];
};

struct addGroupPac
{
  int len;
  int cmd;
  long long groupId;
};

struct toGroupPac
{
  int len;
  int cmd;
  long long groupId;
  char data[];
};

class WritePacManage
{
  public:
    int send_times;

    int fd;//绑定的描述符
    long long userId;//用户id
    int outIndex;//发送的位置
    char * pac;//发送和接受包的空间

    ReadPacManage * rPac;//对应读描述符的pac

    long long currentFriendId;//正在通信的好友ID

    //预连接的状态报文
    bool loginPacSend;//登录包发过？
    bool loginPacSendOver;//某包是否发完?任意包，登录包或数据包
    bool loginPacAck;//登录包回应了

    bool addFriendPacSend;//加好友包
    bool addFriendPacSendOver;
    bool addFriendPacAck;//加好友包回应了
    //发送数据报文，接受数据和状态
    bool pacSend;//已经发送过包数据（该flag目的在于第一次创建数据报）
    bool pacSendOver;//整个包发送完
    bool pacRecv;//已经收到过包的数据
    bool pacRecvOver;//整个包接受完

    WritePacManage(int fdd,long long userIdd,int outIndexx);
    WritePacManage(int fdd,long long userIdd,int outIndexx,bool loginPacSendd,
        bool loginPacSendOverr,bool addFriendPacSendd,bool addFriendPacSendOverr);

    void writeSocket(Epoll &ep,int dataLen);
    void sendLoginPac();
    void sendAddFriendPac(long long friendId);
    void sendFriendPac(long long friendId,int dataLen);
    void sendAddGroupPac();
    void sendGroupPac();

    void set_rPacPtr(ReadPacManage * rPacc);
};

#endif
