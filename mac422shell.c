#include <unistd.h>
#include <signal.h>
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
    scanf( "%[^\n]%*c", input);

    return input;
}

char **
parse_command( char *input)
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

void
protegepracaramba( char *argv[])
{
    chmod( argv[1], 0000);
}

void
liberageral( char *argv[])
{
    chmod( argv[1], 0777);
}

void
rodeveja( char *argv[])
{
    pid_t process_pid;
    pid_t wait_response;
    int stat_loc;
    
    process_pid = fork();

    if (process_pid == -1) {
        perror("fork() failed!");
        _exit(1);
    } else if (process_pid == 0) {
        execve( argv[1], NULL, NULL);
    } else {
        wait_response = waitpid( process_pid, &stat_loc, WUNTRACED);
        printf("=> programa '%s' retornou com codigo %d.\n", argv[1], stat_loc);
    }
}

void
rode( char *argv[])
{
    pid_t process_pid;

    process_pid = fork();

    if (process_pid == -1) {
        perror("fork() failed!");
        _exit(1);
    } else if (process_pid == 0) {
        setsid();
        execve( argv[1], NULL, NULL);
    } else {
        signal( SIGCHLD, SIG_IGN);
    }
}

int 
main( int argc, char const *argv[])
{
    char *input;
    char **command;
    pid_t process_pid;
    pid_t wait_response;
    int stat_loc;

    while (TRUE) {
        input = read_command();
        command = parse_command( input);

        if (!strcmp( command[0], "exit")) {
            free( input);
            free( command);

            break;
        } else if (!strcmp( command[0], "protegepracaramba")) {
            protegepracaramba( command); 
        } else if (!strcmp( command[0], "liberageral")) {
            liberageral( command); 
        } else if (!strcmp( command[0], "rodeveja")) {
            rodeveja( command); 
        } else if (!strcmp( command[0], "rode")) {
            rode( command); 
        } else {
            printf( "command not found: %s\n", command[0]);
        }

        free( input);
        free( command);
    }

    return 0;
}
