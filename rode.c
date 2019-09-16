#define _POSIX_SOURCE

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[])
{
    pid_t child_pid;
    int s;

    child_pid = fork();

    if (child_pid == -1) {
        perror("Unable to fork()!");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        execve( argv[1], NULL, NULL);
    }

    return 0;
}
