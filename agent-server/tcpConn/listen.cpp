#include "cHead.h"

Listen::~Listen()
{

}

void Listen::listenSer()
{

  struct sockaddr_in servAddr;
  
  //绑定服务器ip，端口
  bzero(&servAddr,sizeof(struct sockaddr_in));
  servAddr.sin_family = AF_INET;
  inet_pton(AF_INET,localIp,&(servAddr.sin_addr.s_addr));
  servAddr.sin_port = htons(localPort);
    
  listenSocket = socket(AF_INET,SOCK_STREAM,0);
    
  //端口复用
  if(reuseAddr)
  {
    setReuseAddr(listenSocket);
  }

  //关闭nagle算法
  if(nagle)
  {
    setNagle(listenSocket);
  }

  if(ipBind && portBind)
  {
    if(bind(listenSocket,(struct sockaddr*)&servAddr,sizeof(struct sockaddr)) == -1)
    {
      cout << "bind error!\n";
      cout << "errno: " << errno << endl;
    }
  }
  listen(listenSocket,1000000); 
}


int Listen::run()
{
  struct sockaddr_in cliAddr;
  socklen_t cliLen = sizeof(struct sockaddr);
  int serSocket = accept(listenSocket,(struct sockaddr *)&cliAddr,&cliLen);
  
  //端口复用
  if(reuseAddr)
  {
    setReuseAddr(listenSocket);
  }

  //关闭nagle算法
  if(nagle)
  {
    setNagle(listenSocket);
  }
  //设置非阻塞
  if(nonBlock)
  {
    setNonBlock(listenSocket);
  }

  sock.push_back(serSocket);   
  return serSocket;
}


int Listen::getListenSocket()
{
  return listenSocket;
}
