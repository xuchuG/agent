#ifndef _CLIMANAGE_H_
#define _CLIMANAGE_H_

#include "pacManage.h"
#include "sesion.h"
class CliManage
{
  private:
    PacManage pm;
    Sesion sesion;
  public:
    CliManage(PacManage pmm,Sesion sesionn);
    void readOp();
    void writeOp();
}

#endif
