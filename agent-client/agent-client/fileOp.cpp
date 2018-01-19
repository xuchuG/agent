#include "fileOp.h"

string FileOp::readFile(const char* fileName,int len)
{
  string s;//返回读到的串
  ifstream in(fileName);
  if(!in)
  {
    cerr << "open error!" << endl;
    exit(-1);
  }
  char *buf = (char *)malloc(sizeof(char)*(len+1));
  in.getline(buf,len+1,'z');//使用in.read函数有错
  s = buf;
  //cout << s.size();
  free(buf);
  return s;
}

void FileOp::writeFile(const char* fileName)
{
  ofstream out(fileName);
  if(!out)
  {
    cerr << "open error!" << endl;
    exit(-1);
  }
  int count = 0;//记录扫描到了第几轮，一轮为(a-i)
  for(int i=0;i < 200000; i++)
  {
    int flag = i % 10;
    char c = 'a' + flag - 1;//待写入的字符
    if(flag == 0)
    {
      char c = '0' + count%10;
      count ++;
      out << c;
      continue;
    }
    out << c;
  }
}

