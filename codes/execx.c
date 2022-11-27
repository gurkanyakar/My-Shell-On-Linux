#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

int main(int argc, char *argv[])
{

    char s[80];
    read(3, s, 80);
    printf("---%s", s);
    int inputSize = 1;
    char *token = strtok(s, " ");
    int i = 0;
    for(int x=0; x<250; x++)
        {
            if(s[x] == ' '){
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
    if(strcmp(array[1],"writef")==0){
        printf("test");
        for(int j=0;j<count;j++){
            
        }
    }
}