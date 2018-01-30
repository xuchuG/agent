#include "writePacManage.h"
#include <stdlib.h>
#include <time.h>

extern int Send_Times;
extern string Send_Data;

WritePacManage::WritePacManage(int fdd,long long userIdd,int outIndexx)
{
  send_times = 0;
  fd = fdd;
  userId = userIdd;
  outIndex = outIndexx;
  pac = NULL;
  loginPacSend = false;
  loginPacSendOver = false;
  loginPacAck = false;
  addFriendPacSend = false;
  addFriendPacSendOver = false;
  addFriendPacAck = false;
  pacSend = false;
  pacRecvOver = false;
  pacRecv = false;
  pacRecvOver = false;
}
WritePacManage::WritePacManage(int fdd,long long userIdd,int outIndexx,bool loginPacSendd,
        bool loginPacSendOverr,bool addFriendPacSendd,bool addFriendPacSendOverr)
{
  send_times = 0;
  fd = fdd;
  userId = userIdd;
  outIndex = outIndexx;
  pac = NULL;
  loginPacSend = loginPacSendd;
  loginPacSendOver = loginPacSendOverr;
  //loginPacAck = false;?
  addFriendPacSend = addFriendPacSendd;
  addFriendPacSendOver = addFriendPacSendOverr;
  //addFriendPacAck = false;?
  pacSend = false;
  pacRecvOver = false;
  pacRecv = false;
  pacRecvOver = false;
}

void WritePacManage::writeSocket(Epoll &ep,int dataLen)
{
    if(send_times == Send_Times){
        return;
    }

  if(!loginPacSendOver)//登录包没发或没发完
  {
    sendLoginPac();
  }
  else if(!addFriendPacSendOver && loginPacAck)//加好友包没发或没发完
  {
    //随机产生好友
    sleep(1);
    /*srand((unsigned)time(NULL));
    int base = rand()%2 + 1;*/


    //cout << "add friend base:" << base<<endl;

    long long friendId;
    if(this->userId%2==0){//0和1成对
        friendId = this->userId + 1;
    }
    else{
        friendId = this->userId - 1;
    }
    cout << "query userId: " << friendId << endl;
    this->currentFriendId = friendId;
    sendAddFriendPac(friendId);
  }
  else if(!pacSendOver && addFriendPacAck)//给好友发消息没发或者没发完
  {
    long long friendId = this->currentFriendId;
    sendFriendPac(friendId,dataLen);
    if(pacSendOver)
    {
      //控制数据恢复默认值  控制发送状态报文的flag不需要变化
      outIndex = 0;
      free(pac);
      pac = NULL;
      pacSend = false;
      pacSendOver = false;

      send_times++;

    }
  }
}

void WritePacManage::sendLoginPac()
{
  //组包
  int loginPacLen = 16;
  if(!loginPacSend)
  {
    pac = (char *)malloc(sizeof(struct loginPac));
    ((struct loginPac*)pac)->len = loginPacLen;
    ((struct loginPac*)pac)->cmd = LoginCmd;
    ((struct loginPac*)pac)->userId = userId;
    loginPacSend = true;
  }

  //发包
  int count = 0;
  if((count = write(fd,pac+outIndex,loginPacLen-outIndex)) < 0)
  {
    if(errno != EWOULDBLOCK && errno != EINTR)
    {
      cerr << "write error to socket!\n";
    }
  }
  else
  {
    outIndex += count;
  }

  if(outIndex == loginPacLen)
  {
    free(pac);
    pac = NULL;
    outIndex = 0;
    loginPacSendOver =  true;

    //将读数据的套接字对应的pac里的
    //loginPacSendOver置为true
    rPac->loginPacSendOver = true;

    cout<< userId  <<"登录包发完！\n";
  }
}

void WritePacManage::sendAddFriendPac(long long friendId)
{
  //组包
  int addFriendPacLen = 16;
  if(!addFriendPacSend)
  {
    if(pac == NULL)
    {
      pac = (char *)malloc(sizeof(struct addFriendPac));
      ((struct addFriendPac*)pac)->len = addFriendPacLen;
      ((struct addFriendPac*)pac)->cmd = AddFriendCmd;
      ((struct addFriendPac*)pac)->friendId = friendId;
      addFriendPacSend = true;
    }
  }

  //发包
  int count = 0;
  if((count = write(fd,pac+outIndex,addFriendPacLen-outIndex)) < 0)
  {
    if(errno != EWOULDBLOCK && errno != EINTR)
    {
      cerr << "write error to socket!\n";
    }
  }
  else
  {
    outIndex += count;
  }

  if(outIndex == addFriendPacLen)
  {
    free(pac);
    pac = NULL;
    outIndex = 0;
    addFriendPacSendOver =  true;
    loginPacAck = false;
    //
    rPac->addFriendPacSendOver = true;

    cout << userId << "加好友包发送完！\n";
  }
}

void WritePacManage::sendFriendPac(long long friendId,int dataLen)
{
   //组包
  int packageLen = HeadSize+dataLen;
  if(!pacSend)
  {
    if(pac == NULL)
    {
      pac = (char *)malloc(sizeof(struct toFriendPac)+dataLen);
      ((struct toFriendPac*)pac)->len = packageLen;
      ((struct toFriendPac*)pac)->cmd = ToFriendCmd;
      ((struct toFriendPac*)pac)->friendId = friendId;
      //加数据部分
      //FileOp fOp;
      //string s = fOp.readFile("data.txt",dataLen);
      strcpy(((struct toFriendPac*)pac)->data,Send_Data.c_str());
      pacSend = true;
    }
  }

  //发包
  int count = 0;
  if((count = write(fd,pac+outIndex,packageLen-outIndex)) < 0)
  {
    if(errno != EWOULDBLOCK && errno != EINTR)
    {
      cerr << "write error to socket!\n";
    }
  }
  else
  {
    outIndex += count;
  }

  if(outIndex == packageLen)
  {
    pacSendOver =  true;
  }

}

void WritePacManage::set_rPacPtr(ReadPacManage * rPacc)
{
  rPac = rPacc;
}

