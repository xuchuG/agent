#include "cHead.h"
#include "connect.h"

Connect::~Connect()
{

}

void Connect::run()
{
  struct sockaddr_in servAddr,cliAddr;
  
  //客户端绑定ip
  bzero(&cliAddr,sizeof(struct sockaddr_in));
  cliAddr.sin_family = AF_INET;
  inet_pton(AF_INET,localIp,&(cliAddr.sin_addr.s_addr));
  //cliAddr.sin_port = htons((short)9866);
  

  //绑定服务器ip，端口
  bzero(&servAddr,sizeof(struct sockaddr_in));
  servAddr.sin_family = AF_INET;
  inet_pton(AF_INET,remoteIp,&(servAddr.sin_addr.s_addr));
  servAddr.sin_port = htons(remotePort);
    
  for(int i=0; i<linkNum; i++)
  {
    int cliSocket = socket(AF_INET,SOCK_STREAM,0);
    
    //端口复用
    if(reuseAddr)
    {
      setReuseAddr(cliSocket);
    }
    //关闭nagle算法
    if(nagle)
    {
      setNagle(cliSocket);
    }

    //客户端套接字绑定ip
    if(ipBind)
    {
      if(bind(cliSocket,(struct sockaddr*)&cliAddr,sizeof(struct sockaddr)) == -1)
      {
        cout << "bind error!\n";
        cout << "errno: " << errno << endl;
      }
    }

    if(connect(cliSocket,(struct sockaddr *)&servAddr,sizeof(struct sockaddr)) < 0)
    {
      cout << "connect error!\n";
      cout << "errno: " << errno << endl;
    }

    //连接建立后设置非阻塞
    if(nonBlock)
    {
      setNonBlock(cliSocket);
    }

    sock.push_back(cliSocket);
    //cout << i << endl;
  }
}

vector<int>& Connect::getSock()
{
  return sock;
}

void Connect::operator=(Connect& conn)
{
  this->sock = conn.getSock();
  this->linkNum = conn.linkNum;
  this->localIp = conn.localIp;
  this->localPort = conn.localPort;
  this->remoteIp = conn.remoteIp;
  this->remotePort = conn.remotePort;
  this->ipBind = conn.ipBind;
  this->portBind = conn.portBind;
  this->nonBlock = conn.nonBlock;
  this->nagle = conn.nagle;
  this->reuseAddr = conn.reuseAddr;

}
