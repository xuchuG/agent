#include "sesion.h"

Sesion::Sesion(long long userIdd)
{
  userId = userIdd;  
}

void Sesion::setCurrentFriendId(long long friendId)
{
  currentFriendId = friendId;
}

long long Sesion::getCurrentFriendId()
{
  return currentFriendId;
}

void Sesion::addFriendId(long long friendId)
{
  allFriendId.push_back(friendId);
}

void Sesion::printfAllFriendId()
{
  cout << "用户：" << userId << "的好友分别为：";
  for(int i=0; i<allFriendId.size(); i++)
  {
    cout << allFriendId[i] << " ";
  }
  cout << endl;
}
