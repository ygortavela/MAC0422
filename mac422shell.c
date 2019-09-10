#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define BUFFER 64

char *read_command( void);
char **parse_command( char *input);

int main( int argc, char *argv[])
{
    char *input;
    char **command;
    pid_t child_pid;
    pid_t wait_response;
    int stat_loc;

    while (TRUE) {
        input = read_command();
        command = parse_command( input);

        child_pid = fork();

        if (child_pid == 0) {
            execvp( command[0], command);
        } else {
            wait_response = waitpid( child_pid, &stat_loc, WUNTRACED);
        }

        free( input);
        free( command);
    }

    return 0;
}

char *read_command( void)
{
    char *input = malloc( BUFFER * sizeof (char));

    printf( "> ");
    scanf( "%[^\n]%*c", input);

    return input;
}

char **parse_command( char *input)
{
    char **commmand = malloc( strlen( input) * sizeof (char *));
    char *parsed = strtok( input, " ");
    int index = 0;

    while (parsed != NULL) {
        commmand[index++] = parsed;
        parsed = strtok( NULL, " ");
    }

    commmand[index] = NULL;

    return commmand;
}
