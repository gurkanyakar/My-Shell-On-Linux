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

    char s[80]; // input for pipe read
    read(3, s, 80); // read from pipe
    //printf("%s", s);
    int inputSize = 1; // input size
    char *token = strtok(s, " "); 
    int i = 0;
    for (int x = 0; x < 80; x++) // calculate inmut size
    {
        if (s[x] == ' ') 
        {
            inputSize++; // count input size
        }
    }

    char *array[inputSize]; // create array for input
    while (token != NULL)
    {
        array[i++] = token; // add input to array
        token = strtok(NULL, " "); // split input
    }

    int count = 0;
    count = atoi(array[0]); // array [0] is count atoi is convert string to int
    char str[80];
    
    int pid;
    int ev;
    //printf("execx calisti..");
    if (strcmp(array[1], "writef") == 0)
    {
        strcpy(str, array[3]); // 0 count 1 writef 2 -f 3 file.txt
    char *filename = str;
        for (int i = 0; i < count; i++)
        {
            ev = 0;
            pid = fork(); // fork
            
            if (pid == 0) // child process
            {
                // printf("Process: %8d -- i = %d\n", getpid(), i);
                write(4, filename, strlen(filename));
                ev = execv("writef", NULL);
                perror("");
            }
            else // parent process
            {
                wait(&ev); // wait child process
            }
        }
    }
    else if (strcmp(array[1], "ls\n") == 0 || strcmp(array[1], "ls") == 0)
    {
        for (int i = 0; i < count; i++)
        {
            ev = 0;
            pid = fork();
            if (pid == 0) // child process
            {
                ev = execvp("/bin/ls", NULL); // exec for ls
            }
            else
            {
                wait(&ev); // wait child process
            }
        }
    }
    return 0;
}
