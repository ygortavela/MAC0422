#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define TRUE 1
#define BUFFER 1000

char * read_command() 
{
    char * input = malloc(BUFFER * sizeof(char));
    printf(">");
    scanf("%[^\n]%*c",input);
    return input;
}

char **parse_command(char *input)
{
    char **commmand = malloc(strlen(input) * sizeof(char *));
    char *parsed = strtok(input, " ");
    int index = 0;

    while (parsed != NULL) {
        commmand[index] = parsed;
        index++;
        parsed = strtok(NULL, " ");
    }

    commmand[index] = NULL;
    return commmand;
}

int main(int argc, char const *argv[])
{
    char *input;
    char **command;
    __pid_t child_pid;
    __pid_t result_wait;
    int stat_loc;
    while (TRUE) {
        input = read_command();
        command = parse_command(input);

        if (strcmp(input, "exit") == 0)
            return 0;

        child_pid = fork();

        if (child_pid == 0) {

            execvp(command[0], command);

        }else {

            result_wait = waitpid(child_pid, &stat_loc, WUNTRACED);

        }

        free(input);
        free(command);
    }

}