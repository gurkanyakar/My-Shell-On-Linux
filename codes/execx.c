#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>


int main(int argc, char *argv[])
{

    char s[80];
    read(3, s, 80);
    printf("%s", s);
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
        char str[80];
        strcpy(str, array[3]); // 0 count 1 writef 2 -f 3 file.txt
        char *isim = str;
        int pid;
        int ev;
        for (int i = 0; i < count; i++)
        {
            ev = 0;
            pid = fork();
            if (pid == 0)
            {   
                //printf("Process: %8d -- i = %d\n", getpid(), i);
                write(4, isim, strlen(isim));
                ev = execv("writef", NULL);
                perror("");
                
            }else{
                wait(&ev);
            }
            
            
        }
    }
}