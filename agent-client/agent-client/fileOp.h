#ifndef _FILE_OP_H_
#define _FILE_OP_H_
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;

class FileOp
{
  
  public:
    string readFile(const char* fileName,int len);//读取长度为len的串
    void writeFile(const char* fileName);

};

#endif
