#include "sesion.h"

void Sesion::insertId(long long id,PacManage* pm)
{
  pair<map<long long,PacManage*>::iterator,bool> ret;
  ret = sigleIdMap.insert(pair<long long,PacManage*>(id,pm));
  if(ret.second)
  {
   // cout << "map insert sucess!\n";
  }
  else
  {
    cout << "sigleIdMap insert error!\n";
  }
  
  //同时为插入好友做准备工作
  pair<map<long long,map<long long,PacManage*> >::iterator,bool> rett;
  map<long long,PacManage*> friendMap;
  rett = friendRelationMap.insert(pair<long long,map<long long,PacManage*> >(id,friendMap));
  if(rett.second)
  {
   // cout << "map insert sucess!\n";
  }
  else
  {
    cout << "friendRelationMap insert error!\n";
  }
}

PacManage * Sesion::findId(long long friendId)
{
  map<long long,PacManage*>::iterator it;
  it = sigleIdMap.find(friendId);
  if(it == sigleIdMap.end())
  {
    cout << "查找失败！\n";
    return NULL;   
  }
  return it->second;
}

void Sesion::insertFriendId(long long userId,long long friendId,PacManage* pm)
{
  //首先找到该用户对应的 friend map
  map<long long,map<long long,PacManage*> >::iterator it;
  it = friendRelationMap.find(userId);
  if(it == friendRelationMap.end())
  {
    cout << "在好友关系表中没有该用户！\n";
  }

  //将好友插入到表中
  pair<map<long long,PacManage*>::iterator,bool> ret;
  ret = it->second.insert(pair<long long,PacManage*>(friendId,pm));
  if(ret.second)
  {
   // cout << "map insert sucess!\n";
  }
  else
  {
    cout << "friendRelationMap insert a friendId  error!\n";
  } 
}
