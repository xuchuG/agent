#include "cHead.h"
#include "sesion.h"

PacManage::PacManage(int fdd,int inIndexx,int outIndexx)
{
  fd = fdd;
  inIndex = inIndexx;
  outIndex = outIndexx;
  recvPac = NULL;
  sendQueList = NULL;
  sqlEmpty = true;
  pacRecv = false;
  dataPacRecv = false;
  pacRecvOver = false;
  pacSend = false;
  pacSendOver = false;
}

void PacManage::readSocket(Epoll &ep,Sesion &sesion)
{
  if(!pacRecvOver) 
  {
    recv_Pac(ep,sesion);
/*    if(pacRecvOver)
    {
      ep.modify_event(this,EPOLLOUT);
    }*/
  }
}

void PacManage::recv_Pac(Epoll & ep,Sesion & sesion)
{
  if(!pacRecv) 
  {
    recvPac = (char*)malloc(sizeof(char)*HeadSize);//第一次初始化报头格式报文
    pacRecv = true;
  }  

  //收包
  if(inIndex < HeadSize)//接受头部格式报文
  { 
    int count;
    if((count=read(fd,recvPac+inIndex,HeadSize-inIndex)) < 0)
    {
      if((errno!=EWOULDBLOCK) && (errno!=EINTR))
      {
        cerr << "read error!\n";
        cerr << "error is " << errno << endl;
        cerr << strerror(errno) << endl;
      }
    }
    else if(count==0)//客户端退出
    {
    
    }
    else
    {
      inIndex += count;
    }
    //报头接受完？
    if(inIndex == HeadSize)
    {
      int len = *((int*)recvPac);
      int cmd = *((int *)(recvPac+HeadLenSize));
      if((len==HeadSize) && (cmd==0))//接受到的是登录报文   
      {
        //free(recvPac);
        //重新组包,省一次malloc,利用之前的recvPac
        //recvPac = (char *)malloc()
        long long localId = *((long long *)(recvPac+LenAndCmd));
        //加入map  键-》值   id-》Pacmanage*
        sesion.insertId(localId,this);      
        //userId 标识用户
        this->userId = localId;  
        cout << *((long long *)(recvPac+8)) << "----" << "登录成功！" << endl;    
        ((ackLoginPac *)recvPac)->len = AckPacSize;
        ((ackLoginPac *)recvPac)->ackCmd = AckCmd;
        ((ackLoginPac *)recvPac)->stateNo = OperSuc; 
        
        sendQueList = (SendQueList *)malloc(sizeof(SendQueList)+AckPacSize);
        if(memcpy(sendQueList->sendPac,recvPac,AckPacSize) == NULL)
        {
          cerr << "memcpy error!\n";
        }
        sendQueList->nextPac = NULL;
        sqlEmpty = false;

        free(recvPac);
        recvPac = NULL;
     
        inIndex = 0;
        pacRecvOver = false;
        pacRecv = false;

        //将自己变为可发送状态
        ep.modify_event(this,EPOLLOUT);

        return;  
      }
      else if((len==HeadSize) && (cmd==1))//接受到的是加好友报文   
      {
        long long remoteId = *((long long*)(recvPac+LenAndCmd));
        PacManage * pm = sesion.findId(remoteId);
        //加入好友关系表中
        sesion.insertFriendId(this->userId,remoteId,pm);
        if(pm != NULL)
        {
          cout << userId << "--添加好友-" << *((long long *)(recvPac+8)) << "-成功！" << endl;    
          friendId =  remoteId;
          fdFriend = pm->fd;//添加好友描述符，方便下次直接可以转发数据

          ((ackAddFriendPac *)recvPac)->len = AckPacSize;
          ((ackAddFriendPac *)recvPac)->ackCmd = AckAddFriendCmd;
          ((ackAddFriendPac *)recvPac)->stateNo = OperSuc; 
        }
        else
        {
          cout << "添加好友失败！\n";
          ((ackAddFriendPac *)recvPac)->len = AckPacSize;
          ((ackAddFriendPac *)recvPac)->ackCmd = AckAddFriendCmd;
          ((ackAddFriendPac *)recvPac)->stateNo = OperFal; 
        }

        sendQueList = (SendQueList *)malloc(sizeof(SendQueList)+AckPacSize);
        memcpy(sendQueList->sendPac,recvPac,AckPacSize);
        sendQueList->nextPac = NULL;
        sqlEmpty = false;

        cout <<*(int*)sendQueList->sendPac<<endl;
        cout <<*(int*)(sendQueList->sendPac+4)<<endl;
        free(recvPac);
        recvPac = NULL;


        inIndex = 0;
        pacRecvOver = false;
        pacRecv = false; 

        //自己变为可发送状态
        ep.modify_event(this,EPOLLOUT);

        return;  
      }
    }
  }
  else//接受数据部分
  {
    int len = *((int*)recvPac);
    int cmd = *((int *)(recvPac+HeadLenSize));
    if((len>HeadSize) && (cmd==2))//接受到的是发好友的数据报文   
    {
        sleep(3);
        long long remoteId = *((long long*)(recvPac+LenAndCmd));
        if(remoteId == friendId)//要发往好友的id已经被记录了
        {
        }
        else//没有加好友，先做简单版的处理，马上可以加为好友
        {
          cout <<"len:" <<len<<endl;
          cout << "remoteId:" << remoteId<<endl;
          PacManage * pm = sesion.findId(remoteId);
          if(pm != NULL)
          {
            friendId =  remoteId;
            fdFriend = pm->fd;
            //fdAgent = fdFriend;   
          }
          else
          {
            cout << "添加好友失败！\n";
          }
        }
        if(!dataPacRecv)
        {
          char *pacBef = recvPac;
          recvPac = (char *)realloc(recvPac,len*sizeof(char));
          if(recvPac == NULL)
          {
            cout << "realloc memory error!\n";
          } 
          dataPacRecv = true;
        }     
        int count;
        if((count=read(fd,recvPac+inIndex,len-inIndex)) < 0)
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
        if(inIndex == len)//接受完所有的报头和数据
        {
          //更改包的内容 friendIp -> userId
          ((struct package *)recvPac)->userId = this->userId;        
          //pacRecvOver = true;
   
          //先查表获得对方的发送缓冲区的位置
          PacManage * remotePac = sesion.findId(remoteId);
          if(remotePac != NULL)
          {
          }
          else
          {
            cerr << "好友不在线！\n";
          }
          
          if(!remotePac->sendQueList->add_Pac(ep,remotePac,recvPac,len))         
          {
            cerr << "往对方发送缓冲区中添加包error！\n";
          }
          free(recvPac);
          recvPac = NULL;

          inIndex = 0;
          pacRecvOver = false; 
          pacRecv = false;
          dataPacRecv = false;

          return; 
        }
    }
  }
}

void PacManage::writeSocket(Epoll &ep)
{
  if(!pacSendOver)//包没发或没发完
  {
    sendPac(ep); 
    /*if(pacSendOver)//改注册事件
    {
      //控制数据恢复默认
      inIndex =  0;
      outIndex = 0;
      free(pac);
      pac = NULL;
      pacRecv = false;
      dataPacRecv = false; 
      pacRecvOver = false;
      pacSend = false;
      pacSendOver = false;

      ep.modify_event(this,EPOLLIN);    
    }*/
  }
}  

void PacManage::sendPac(Epoll &ep)
{
  //发包
  //int count = 0;
  //int fdAgent = fd;
  /*if(pacRecvOver && dataPacRecv)//要发送的是给好友的报文
  {
    fdAgent = fdFriend; 
  }*/
  if(!sendQueList->send_Que_list(ep,this))  
  {
    cerr << "发送缓冲队列出错！\n";
  }
} 

bool PacManage::SendQueList::add_Pac(Epoll &ep,PacManage* remotePac,char * recvPac,int len)
{
  if(remotePac->sqlEmpty) 
  {
    remotePac->sendQueList = (SendQueList *)malloc(sizeof(SendQueList)+len);
    memcpy(remotePac->sendQueList->sendPac,recvPac,len);
    remotePac->sendQueList->nextPac = NULL;
    remotePac->sqlEmpty = false;
    
    //cout << "add pac" << *(int *)remotePac->sendQueList->sendPac<<endl;
    //将对方置为可接受发送状态
    ep.modify_event(remotePac,EPOLLIN | EPOLLOUT);

  }
  else
  {
    cout << "list\n";
    SendQueList * p = remotePac->sendQueList;
    while(p->nextPac != NULL)
    {
      p = p->nextPac;
    }
    SendQueList* q = (SendQueList *)malloc(sizeof(SendQueList)+len);
    memcpy(q->sendPac,recvPac,len);
    q->nextPac = NULL;
    
    p->nextPac = q; 

  }
  return true;
}

bool PacManage::SendQueList::send_Que_list(Epoll &ep,PacManage * ownPac)
{
  int count = 0;
  while(ownPac->sendQueList != NULL)
  {
     /*cout << *(int *)(ownPac->sendQueList->sendPac)<<endl;
     cout << *(int *)(ownPac->sendQueList->sendPac+8)<<endl;
     if(*(int*)(ownPac->sendQueList->sendPac+4) == 1)
     exit(1);*/
    if((count = write(ownPac->fd,ownPac->sendQueList->sendPac+ownPac->outIndex,*(int *)(ownPac->sendQueList->sendPac)-ownPac->outIndex)) < 0)
    {
      if(errno != EWOULDBLOCK && errno != EINTR)
      {
        cerr << "write error to socket!\n"; 
      }
      else if(errno == EWOULDBLOCK)
      {
        break;
      }
    } 
    else
    {
      ownPac->outIndex += count;     
    }
    if(ownPac->outIndex == *(int *)(ownPac->sendQueList->sendPac))
    {
      //cout <<ownPac->outIndex <<  "write over\n";
      ownPac->outIndex = 0;
      SendQueList * tmp = ownPac->sendQueList;
      ownPac->sendQueList = ownPac->sendQueList->nextPac; 
      free(tmp);
    }
  }
  if(ownPac->sendQueList == NULL)
  {
    ownPac->sqlEmpty = true;
    
    //发送缓冲队列中数据发送完成，关闭发送功能
    ep.modify_event(ownPac,EPOLLIN); 

  }
  return true;
}
