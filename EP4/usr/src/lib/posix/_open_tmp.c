/* ######################################################## */
#include <lib.h>
#define open	_open
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

PUBLIC int open_tmp(name, mode)
_CONST char *name;
_CONST char *mode;
{
  int flags, rwmode = 0, rwflags = 0;
  va_list argp;
  message m;

  switch(*mode++) {
    case 'r':
      rwmode = O_RDONLY;
      break;
    case 'w':
      rwmode = O_WRONLY;
      rwflags = O_CREAT | O_TRUNC;
      break;
    case 'a': 
      rwmode = O_WRONLY;
      rwflags |= O_APPEND | O_CREAT;
      break;         
    default:
      perror("unrecognized input mode");
      return (EXIT_FAILURE);
  }

  if (*mode++ == '+') rwmode = O_RDWR;

  flags = rwmode | rwflags;

  va_start(argp, flags);

  if (flags & O_CREAT) {
    m.m1_i1 = strlen(name) + 1;
    m.m1_i2 = flags;
    m.m1_i3 = va_arg(argp, _mnx_Mode_t);
    m.m1_p1 = (char *) name;
  } else {
    _loadname(name, &m);
    m.m3_i2 = flags;
  }

  va_end(argp);

  return(_syscall(FS, OPENTMP, &m));
}

/* ######################################################## */
