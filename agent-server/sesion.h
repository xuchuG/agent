#ifndef _SESION_H_
#define _SESION_H_
#include <map>
#include "pacManage.h"
#include <iostream>
using namespace std;

class Sesion
{
  private:
    //分两个map的原因：职责分开，有利于功能拓展
    map<long long,PacManage*> sigleIdMap;//存所有在线的用户
    map<long long,map<long long,PacManage*> > friendRelationMap;//存每个在线用户的好友，中间的那个map存对应用户的所有好友
  public:
    void insertId(long long id,PacManage* pm);
    PacManage * findId(long long friendId);
    void insertFriendId(long long userId,long long friendId,PacManage* pm);
};

#endif
