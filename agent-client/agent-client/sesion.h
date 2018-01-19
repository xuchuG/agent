#ifndef _SESION_H_
#define _SESION_H_

#include <vector>
using namespace std;

class Sesion
{
  private:
   long long userId;//该客户端ID
   long long currentFriendId;//当前正在聊天的好友id 
   vector<long long> allFriendId;//所有的好友
  public:
   Sesion(long long userIdd);
   void setCurrentFriendId(long long friendId);
   void addFriendId(long long friendId);
   long long getCurrentFriendId();
   void printfAllFriendId();
};

#endif
