/* ######################################################## */
#include <lib.h>
#include <unistd.h>

PUBLIC int batch(pid)
pid_t pid;
{
  message m;

  m.m1_i1 = pid;
  m.m1_i2 = getpid();

  return(_syscall(MM, BATCH, &m));
}
/* ######################################################## */
