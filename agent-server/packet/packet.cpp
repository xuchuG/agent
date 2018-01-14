#include "packet.h"

void Packet::MakeErrorAck(int stateNo,char*& head,char*& tail)
{
    head = new char[HeadSize];
    tail = head + HeadSize;
    ((struct head *)head)->len = HeadSize;
    ((struct head *)head)->cmd = stateNo;
    ((struct head *)head)->id = 0;
}

void Packet::MakeSucAck(int stateNo,char*& head,char *& tail)
{
    head = new char[HeadSize];
    tail = head + HeadSize;
    ((struct head *)head)->len = HeadSize;
    ((struct head *)head)->cmd = stateNo;
    ((struct head *)head)->id = 0;
}

