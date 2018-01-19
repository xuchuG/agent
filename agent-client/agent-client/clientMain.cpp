#include "cHead.h"
#include "connect.h"
#include "epoll.h"
#include "readPacManage.h"
#include "writePacManage.h"

int dataLen;

int main(int argc,char **argv)
{
  int linkNum;
  char * localIp;
  char * remoteIp;
  short remotePort;
  cout << "示例：" << "./client 本地ip 目的ip 目的端口 连接数 报文大小\n";
  if(argc < 6)
  {
    cout << "parameter is too few!\n";
    return 0;
  }
  if(argv[1])
  {
    localIp = argv[1];
    cout << localIp << endl;
  }
  if(argv[2])
  {
    remoteIp = argv[2];
    cout << remoteIp << endl;
  }
  if(argv[3])
  {
    remotePort = (short)atoi(argv[3]);
    cout << remotePort << endl;
  }
  if(argv[4])
  {
    linkNum = atoi(argv[4]);
    cout << linkNum << endl;
  }
  if(argv[5])
  {
    dataLen = atoi(argv[5]);
    cout << dataLen << endl; 
  }

  //建立linkNum个连接
  Connect conn(linkNum,localIp,remoteIp,remotePort,true,false,true,true,true);
  conn.run();
  
  int echoTimes =  0;
  //epoll注册，监听事件
  Epoll ep1(linkNum);
  ep1.init(conn);
  for(;;)
  {
    ep1.run();
    struct epoll_event * events = ep1.getEpollEvents();
    for(int i=0; i<ep1.getEvCount(); i++)
    {
      if(events[i].events & EPOLLOUT)
      {
        WritePacManage *pac = (WritePacManage *)events[i].data.ptr;
        pac->writeSocket(ep1,dataLen); 
      }
      else if(events[i].events & EPOLLIN)
      {
        ReadPacManage *pac = (ReadPacManage *)events[i].data.ptr;
        pac->readSocket(ep1); 
      }
    }
  }  
  return 0;
}
