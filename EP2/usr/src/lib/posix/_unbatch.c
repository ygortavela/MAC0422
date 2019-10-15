/* ######################################################## */
#include <lib.h>
#include <unistd.h>

PUBLIC int unbatch(proc_id)
pid_t proc_id;
{
  message m;

  m.m1_i1 = proc_id;
  m.m1_i2 = getpid();

  return(_syscall(MM, UNBATCH, &m));
}
/* ######################################################## */
