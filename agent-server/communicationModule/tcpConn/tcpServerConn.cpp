#include "tcpServerConn.h"
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

int TcpServerConn::tcpListen(char ip[],short port){
    struct sockaddr_in servAddr;

    //绑定服务器ip，端口
    bzero(&servAddr,sizeof(struct sockaddr_in));
    servAddr.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&(servAddr.sin_addr.s_addr));
    servAddr.sin_port = htons(port);

    int listen_socket;
    if((listen_socket = socket(AF_INET,SOCK_STREAM,0) < 0){
        cerr << "TcpServerConn::tcpListen : socket error!\n";
        cerr << "errno: " << errno << endl;
    }

    //端口复用
    setReuseAddr(listen_socket);

    //关闭nagle算法
    setNagle(listen_socket);

    if(bind(listen_socket,(struct sockaddr*)&servAddr,
            sizeof(struct sockaddr)) == -1){
        cerr << "TcpServerConn::tcpListen : bind error!\n";
        cerr << "errno: " << errno << endl;
    }

    if(listen(listen_socket,1000000) < 0){
        cerr << "TcpServerConn::tcpListen : listen error!\n";
        cerr << "error: " << errno << endl;
    }
}


int TcpServerConn::tcpAccept(int listen_socket){
    struct sockaddr_in cliAddr;
    socklen_t cliLen = sizeof(struct sockaddr);

    int socket;
    if((socket = accept(listen_socket,(struct sockaddr *)&cliAddr,&cliLen) < 0){
        cerr << "TcpServerConn::tcpAccept : accept error!\n";
        cerr << "errno : " << errno << endl;
    }

    //端口复用
    setReuseAddr(socket);

    //关闭nagle算法
    setNagle(socket);

    //设置非阻塞
    setNonBlock(socket);

    return socket;
}


