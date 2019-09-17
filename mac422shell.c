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

int
rodeveja( char *argv[], char *envp[])
{
    pid_t process_pid;
    pid_t wait_response;
    int stat_loc, status;
    
    argv[0] = argv[1];
    argv[1] = '\0';
    process_pid = fork();

    if (process_pid == -1) {
        perror( "fork() failed!");
        _exit( 1);
    } else if (process_pid == 0) {
        status = execve( argv[0], argv, envp);
        _exit( status);
    } else {
        wait_response = waitpid( process_pid, &stat_loc, WUNTRACED);
        printf( "=> programa '%s' retornou com codigo %d.\n", argv[0], stat_loc);
    }

    return 0;
}

int
rode( char *argv[], char *envp[])
{
    pid_t process_pid;
    int status, fd;

    argv[0] = argv[1];
    argv[1] = '\0';
    process_pid = fork();

    if (process_pid == -1) {
        perror( "fork() failed!");
        _exit( 1);
    } else if (process_pid == 0) {
	setsid();
	chdir( "/");
	close( STDIN_FILENO);
	close( STDOUT_FILENO);
	close( STDERR_FILENO);
	fd = open( "/dev/null", O_RDWR);
	dup( fd);
	dup( fd);
        status = execve( argv[0], argv, envp);
        _exit( status);
    } else {
        signal( SIGCHLD, SIG_IGN);
    }

    return 0;
}

int 
main( int argc, char *argv[], char *envp[])
{
    char *input;
    char **command;
    pid_t process_pid;
    int s;

    while (TRUE) {
        input = read_command();
        command = parse_command( input);

	if (!strcmp( command[0], "exit")) {
            free( input);
            free( command);
            _exit(0);
        } else if (!strcmp( command[0], "protegepracaramba")) {
            protegepracaramba( command); 
        } else if (!strcmp( command[0], "liberageral")) {
            liberageral( command); 
        } else if (!strcmp( command[0], "rodeveja")) {
            rodeveja( command, envp); 
        } else if (!strcmp( command[0], "rode")) {
            s = rode( command, envp); 
        } else {
            printf( "command not found: %s\n", command[0]);
        }

        free( input);
        free( command);
    }

    return 0;
}
