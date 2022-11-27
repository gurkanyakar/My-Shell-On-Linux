#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
int pipefd[2];
void writefFunction(char *filename){
    printf("Topla fonksiyonu cagirildi");
    printf("%d",strlen(filename));
    int ev = 0;
    int pid = fork();
    if (pid == 0)
    { 
        write(pipefd[1], filename, strlen(filename));
        ev = execv("topla", NULL);
        perror("");
        close(pipefd[1]);
    }
    else
    { 
        //write(pipefd[1], filename, strlen(filename));
        wait(&ev);
    }
}


int main(int argc, char *argv[])
{
    
    char str[80];

    strcpy(str, "fix");
    writefFunction(str);
    return 0;
}