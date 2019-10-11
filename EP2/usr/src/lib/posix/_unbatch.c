/* ######################################################## */
#include <lib.h>
#include <unistd.h>

PUBLIC int printmessage(proc_id)
pid_t proc_id;
{
  message m;
  return(_syscall(MM,UNBATCH,&m));
}
/* ######################################################## */
