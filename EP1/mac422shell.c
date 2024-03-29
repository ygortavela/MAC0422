#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define BUFFER 64

char *
read_command( void)
{
    char *input = malloc( BUFFER * sizeof (char));

    printf( "> ");
    input = fgets( input, BUFFER, stdin);
    input = strtok( input, "\n");

    return input;
}

char **
parse_command( char *input)
{
    char **commmand = malloc( strlen(input) * sizeof (char *));
    char *parsed = strtok( input, " ");
    int index = 0;

    while (parsed != NULL) {
        commmand[index++] = parsed;
        parsed = strtok( NULL, " ");
    }

    commmand[index] = NULL;
    free( parsed);

    return commmand;
}

void
protegepracaramba( char *argv[])
{
    int status;

    status = chmod( argv[0], 0000);

    _exit( status);
}

void
liberageral( char *argv[])
{
    int status;

    status = chmod( argv[0], 0777);

    _exit( status);
}

void
rodeveja( char *argv[], char *envp[])
{
    int status;

    status = execve( argv[0], argv, envp);

    _exit( status);
}

void
rode( char *argv[], char *envp[])
{
    int status, fd;

    signal( SIGINT, SIG_IGN);
    signal( SIGQUIT, SIG_IGN);
    close( STDIN_FILENO);

    status = execve( argv[0], argv, envp);
    _exit( status);
}

int
main( int argc, char *argv[], char *envp[])
{
    char *input;
    char **command;
    pid_t process_pid;
    pid_t wait_response;
    int stat_loc, commandCode, i;

    while (TRUE) {
        input = read_command();

        if (input == NULL) {
            free( input);

            continue;
        }

        command = parse_command( input);

        if (!strcmp( command[0], "exit")) {
            free( input);
            free( command);
            _exit(0);
        } else if (!strcmp( command[0], "protegepracaramba")) {
            commandCode = 0;
        } else if (!strcmp( command[0], "liberageral")) {
            commandCode = 1;
        } else if (!strcmp( command[0], "rodeveja")) {
            commandCode = 2;
        } else if (!strcmp( command[0], "rode")) {
            commandCode = 3;
        } else {
            printf( "command not found: %s\n", command[0]);
            free( input);
            free( command);

            continue;
        }

        for (i = 0; command[i] != NULL; i++)
            command[i] = command[i + 1];

        process_pid = fork();

        if (process_pid == -1) {
            perror( "fork() failed!");
            _exit( 1);
        } else if (process_pid == 0) {
            if (commandCode == 0) protegepracaramba( command);
            else if (commandCode == 1) liberageral( command);
            else if (commandCode == 2) rodeveja( command, envp);
            else if (commandCode == 3) rode( command, envp);
        } else {
            if (commandCode == 2) {
                wait_response = waitpid( process_pid, &stat_loc,
                                         WUNTRACED);
                printf( "=> programa '%s' retornou com codigo %d.\n",
                        argv[0], stat_loc);
            } else if (commandCode == 3) {
                signal( SIGCHLD, SIG_IGN);
            }

            free( input);
            free( command);
        }
    }

    return 0;
}
