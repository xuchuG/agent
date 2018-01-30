#include "readPacManage.h"
#include "writePacManage.h"
#include <stdlib.h>
#include <time.h>

extern int linkNum;
extern int Send_Times;
int Total_Recv_Times;

ReadPacManage::ReadPacManage(int fdd,long long userIdd,int inIndexx)
{
  fd = fdd;
  userId = userIdd;
  inIndex = inIndexx;
  pac = NULL;
  loginPacSendOver = false;
  addFriendPacSendOver = false;
  pacRecv = false;
  pacRecvOver = false;
}
ReadPacManage::ReadPacManage(int fdd,long long userIdd,int inIndexx,bool loginPacSendd,
        bool loginPacSendOverr,bool addFriendPacSendd,bool addFriendPacSendOverr)
{
  fd = fdd;
  userId = userIdd;
  inIndex = inIndexx;
  pac = NULL;
  loginPacSendOver = loginPacSendOverr;
  addFriendPacSendOver = addFriendPacSendOverr;
  pacRecv = false;
  pacRecvOver = false;
}

void ReadPacManage::readSocket(Epoll &ep)
{
  if(!pacRecvOver)
  {
    recvPac();
    if(pacRecvOver)
    {
      //控制数据恢复默认值  控制发送状态报文的flag不需要变化
      inIndex = 0;
      free(pac);
      pac = NULL;
      pacRecv  =  false;
      pacRecvOver = false;
    }
  }

}

void ReadPacManage::recvPac()
{
  if(!pacRecv)
  {
    pac = (char*)malloc(sizeof(char)*LenAndCmd);
    pacRecv = true;
  }

  //收包
  if(inIndex < LenAndCmd)//接受头部格式报文
  {
    int count;
    if((count=read(fd,pac+inIndex,LenAndCmd-inIndex)) < 0)
    {
      if((errno!=EWOULDBLOCK) && (errno!=EINTR))
      {
        cerr << "read error from sokcet!\n";
      }
    }
    else if(count==0)//服务器退出
    {

    }
    else
    {
      inIndex += count;
    }
  }
  //报头接受完？
  if(inIndex >= LenAndCmd)
  {
    int len = *((int*)pac);
    int cmd = *((int *)(pac+HeadLenSize));

    cout << "len:"<<len<< "  cmd:"<<cmd<<endl;
    if((len==AckStateSize) && (cmd==3) && loginPacSendOver)//接受到的是登录的回应报文
    {
      //接受回应码
      char * pacBef = pac;
      pac = (char *)realloc(pac,AckStateSize*sizeof(char));
      if(pac == NULL)
      {
        cout << "realloc memory error!\n";
      }
      int count;
      if((count=read(fd,pac+inIndex,AckStateSize-inIndex)) < 0)
      {
        if((errno!=EWOULDBLOCK) && (errno!=EINTR))
        {
          cerr << "read error from sokcet!\n";
        }
      }
      else
      {
        inIndex += count;
      }
      if(inIndex == AckStateSize)
      {
        if(*((int *)(pac+LenAndCmd)) == 0)//状态码为成功
        {
          cout << this->userId << "----" << "登录成功！\n";
        }
        else if(*((int *)(pac+LenAndCmd)) == 1)
        {
           cerr << this->userId << "----" <<"登录失败！\n";
        }
        pacRecvOver = true;

        //下次不再收登录包的ack
        loginPacSendOver = false;
        //写描述符可以发加好友包了
        wPac->loginPacAck = true;

        cout << userId <<  "登录包ack接受完成！\n";
      }
      return;
    }
    else if((len==AckStateSize) && (cmd==4) && addFriendPacSendOver)
    {
      //接受回应码
      pac = (char *)realloc(pac,AckStateSize*sizeof(char));
      if(pac == NULL)
      {
        cout << "realloc memory error!\n";
      }
      int count;
      if((count=read(fd,pac+inIndex,AckStateSize-inIndex)) < 0)
      {
        if((errno!=EWOULDBLOCK) && (errno!=EINTR))
        {
          cerr << "read error from sokcet!\n";
        }
      }
      else
      {
        inIndex += count;
      }
      if(inIndex == AckStateSize)
      {
        if(*((int *)(pac+LenAndCmd)) == 0)//状态码为成功
        {
          cout << this->userId << "----" << "加好友成功！\n";
        }
        else if(*((int *)(pac+LenAndCmd)) == 1)
        {
          cerr << this->userId << "----"  << "加好友失败！\n";
        }

        pacRecvOver = true;

        //接加好友包ack的状态还原
        addFriendPacSendOver = false;
        //对应写描述符可以往好友写数据
        wPac->addFriendPacAck = true;

        cout << userId << "加好友包ack接受完成！\n";
      }
      return;
    }
    else if((len>AckStateSize) && (cmd==2))//接受数据部分
    {
      char * pacBef = pac;
      pac = (char *)realloc(pac,(len+1)*sizeof(char));
      if(pac == NULL)
      {
        cout << "realloc memory error!\n";
      }
      int count;
      if((count=read(fd,pac+inIndex,len-inIndex)) < 0)
      {
        if((errno!=EWOULDBLOCK) && (errno!=EINTR))
        {
          cerr << "read error from sokcet!\n";
        }
      }
      else
      {
        inIndex += count;
      }
      if(inIndex == len)
      {
        pac[len] = '\0';
        cout << this->userId << "收到的消息：" << *(long long *)(pac+LenAndCmd)  << " say:" << (pac+HeadSize) << endl;

        Total_Recv_Times++;
        if(Total_Recv_Times >= linkNum*Send_Times){
            cout << "Total_Recv_Times: " << Total_Recv_Times << endl;
        }

        pacRecvOver = true;
      }
    }
    else//登录包没返回登录包的ack或加好友没返回加好友ack
    {
      cerr << "没有返回对应的包！\n";
        exit(-1);
    }
  }
}

void ReadPacManage::set_wPacPtr(WritePacManage * wPacc)
{
  wPac = wPacc;
}
