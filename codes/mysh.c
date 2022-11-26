#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>

void bashFunction()
{
    int pid = fork();
    if (pid == 0)
    {
        int ev = execvp("bash", NULL);
        perror("");
    }
    else
    {
        wait(&pid);
    }
}
void catFunction(char[] mystring)
{
    printf("catFunction");
}

int main(int argc, char *argv[])
{
    char **inputArray;
    char input[250];
    int inputSize;
    char* myString = "";
    // printf("welcome myshell ! by Gurkan Yakar \n");

    while (1)
    {
        printf("myshell>> ");
        fgets(input, 250, stdin); // read input
        printf("input: %s", input);
        char *token = strtok(input, " ");
        while (token != NULL)
        {
            //printf("%s\n", token);
            if(strcmp(token, "cat") == 0)
            {
                catFunction(input);
                break;
            }
            
            token = strtok(NULL, " ");
        }
        if (strcmp(input, "ls\n") == 0)
        {
            printf("ls was hit\n");
        }
        else if (strcmp(input, "wait\n") == 0)
        {
            printf("wait was hit\n");
        }
        else if (strcmp(input, "exit\n") == 0)
        {
            printf("Cikis yapiliyor..!");
            exit(0);
        }
        else if (strcmp(input, "bash\n") == 0)
        {
            printf("bash was hit\n");
            bashFunction();
        }
        else
        {
            printf("unknown command\n");
        }
    }
    return 0;
}
