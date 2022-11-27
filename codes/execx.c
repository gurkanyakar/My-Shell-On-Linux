#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
int pipefd[2];
int main(int argc, char *argv[])
{
    if (pipe(pipefd) < 0)
    {
        perror("pipe");
        exit(1);
    }

    char s[80];
    read(3, s, 80);
    printf("---%s", s);
    int inputSize = 1;
    char *token = strtok(s, " ");
    int i = 0;
    for (int x = 0; x < 250; x++)
    {
        if (s[x] == ' ')
        {
            inputSize++;
        }
    }

    char *array[inputSize];
    while (token != NULL)
    {
        array[i++] = token;
        token = strtok(NULL, " ");
    }

    int count = 0;
    count = atoi(array[0]);
    if (strcmp(array[1], "writef") == 0)
    {
        // char str[80];

        // strcpy(str, array[3]); // 0 count 1 writef 2 -f 3 file.txt
        int ev = 0;
        int pid = fork();
        if (pid == 0)
        {
            for (int i = 0; i < count; i++)
            {
                write(pipefd[1], array[3], strlen(array[3]));
                ev = execv("writef", NULL);
                perror("");
                close(pipefd[1]);
            }
        }
        else
        {
            // write(pipefd[1], filename, strlen(filename));
            wait(&ev);
        }
    }
}