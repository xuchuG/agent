#ifndef _READPACMANAGE_H_
#define _READPACMANAGE_H_

#include "epoll.h"
#include "fileOp.h"
#include <string.h>

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

class WritePacManage;

class ReadPacManage
{
  public:
    int fd;//绑定的描述符
    long long userId;//用户id
    int inIndex;//读入的位置
    char * pac;//发送和接受包的空间

    WritePacManage *  wPac;//对应写描述符的pac

    long long currentFriendId;//正在通信的好友ID

    //预连接的状态报文
    bool loginPacSendOver;//用来控制此时应该接收服务器返回的登录包ack
    bool addFriendPacSendOver;//用来控制此时接收加好友包的ack
    //接受数据和状态
    bool pacRecv;//已经收到过包的数据
    bool pacRecvOver;//整个包接受完

    ReadPacManage(int fdd,long long userIdd,int inIndexx);
    ReadPacManage(int fdd,long long userIdd,int inIndexx,bool loginPacSendd,
        bool loginPacSendOverr,bool addFriendPacSendd,bool addFriendPacSendOverr);

    void readSocket(Epoll &ep);
    void recvPac();

    void set_wPacPtr(WritePacManage* wPacc);
};

#endif
