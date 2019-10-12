/* ######################################################## */
#include "syslib.h"

/*===========================================================================*
 *                                sys_setprior			     	     *
 *===========================================================================*/
PUBLIC int sys_setprior(int proc, int prio)
{
  message m;

  m.m1_i1 = proc;
  m.m1_i2 = prio;
  return(_taskcall(SYSTASK, SYS_SETPRIOR, &m));
}
/* ######################################################## */
