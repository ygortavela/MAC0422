/* ######################################################## */
#include "../system.h"
#include <minix/type.h>
#include <sys/resource.h>

/*===========================================================================*
 *				  do_setprior *
 *===========================================================================*/
PUBLIC int do_setprior(message *m_ptr)
{
  int proc_nr, pri;
  register struct proc *rp;

  proc_nr = m_ptr->PR_ENDPT;
  pri = m_ptr->PR_PRIORITY;
  rp = proc_addr(proc_nr);

  lock_dequeue(rp);
  rp->p_max_priority = rp->p_priority = pri;
  if (! rp->p_rts_flags) lock_enqueue(rp);

  return(OK);
}
/* ######################################################## */
