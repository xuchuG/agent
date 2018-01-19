#include "fileOp.h"

int main()
{
  FileOp f;
  //f.writeFile("data.txt");
  for(int i=0;i<150;i++)
  {
    string s = f.readFile("data.txt",i);
    cout << s << endl;
  }
  return 0; 
}
