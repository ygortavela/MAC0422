#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int
main( int argc, char *argv[])
{
    pid_t child_pid;
    pid_t wait_response;
    int stat_loc;
    
    child_pid = fork();

    if (child_pid == 0) {
        execve( argv[1], NULL, NULL);
    } else {
        wait_response = waitpid( child_pid, &stat_loc, WUNTRACED);

        printf("=> programa '%s' retornou com codigo %d.\n", argv[1], stat_loc);

        return 0;
    }
}
