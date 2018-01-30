#ifndef _PACKET_H_
#define _PACKET_H_

struct head
{
    int len;
    int cmd;
    long long id;
};

struct pacStandardFormat{
    char* head;
    char* tail;
};

#define HeadSize 16

class Packet
{
    public:
        static void MakeErrorAck(int stateNo,char * & head,
                char * & tail);
        static void MakeSucAck(int stateNo,char * & head,
                char * &tail);
};

namespace PacketCommand
{
    const int LoginCmd = 0;
    const int QueryCmd = 1;
    const int RelayCmd = 2;
    const int EndCmd = 3;
};

namespace AckPacCmd
{
    const int SEQUENCE_ERROR = 0;
    const int ID_ALREADY_EXIST = 1;
    const int USER_OFFLINE = 2;
    const int LOGIN_SUC = 3;
    const int QUERY_SUC = 4;
};
#endif
