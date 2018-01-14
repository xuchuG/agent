#ifndef _TABLEMANAGE_H_
#define _TABLEMANAGE_H_

#include <map>
#include <iostream>
using namespace std;

template<typename TLeft,typename TRight>
class TableManage
{
    private:
        map<TLeft,TRight> table;

    public:
        int insert(TLeft left,TRight right)
        {
            //pair<auto,bool> ret;
            auto ret = table.insert(pair<TLeft,TRight>(left,right));
            if(!ret.second)
            {
                cerr << "table insert error!\n";
                return -1;
            }

            return 0;
        }

        TRight find(TLeft left)
        {
            //map<TLeft,TRight>::iterator it;
            auto it = table.find(left);
            if(it == table.end())
            {
                cerr << "table find error!";
                return NULL;
            }
            return it->second;
        }

        bool isContainsId(TLeft left)
        {
            return table.find(left) != table.end();
        }
};

#endif
