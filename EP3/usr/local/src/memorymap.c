/* ######################################################## */
#include "/usr/src/servers/is/inc.h"
#include "/usr/src/servers/pm/mproc.h"

int
main( int argc, char *argv[])
{
  struct mproc mp[NR_PROCS];
  struct pm_mem_info pmi;
  phys_clicks mem_free;
  int i;

  getsysinfo(PM_PROC_NR, SI_PROC_TAB, mp);
  getsysinfo(PM_PROC_NR, SI_MEM_ALLOC, &pmi);

  printf("Memory map:\n<pid>\t<first pos>\t<last pos>\n");

  for (i = 0; i < NR_PROCS; i++)
    if (mp[i].mp_pid != 0 || i == PM_PROC_NR)
      printf("%d\t0x%x\t\t0x%x\n", mp[i].mp_pid, mp[i].mp_seg[T].mem_phys, mp[i].mp_seg[S].mem_phys + mp[i].mp_seg[S].mem_len);
  
  mem_free = 0;

  for (i = 0; i < _NR_HOLES; i++)
    if (pmi.pmi_holes[i].h_base) mem_free += pmi.pmi_holes[i].h_len;

  printf("Free memory (kB): %d\n", (mem_free << CLICK_SHIFT)/1024);

  return 0;
}
/* ######################################################## */
