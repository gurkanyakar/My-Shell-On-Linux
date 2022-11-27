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
void lsFunction()
{
    int pid = fork();
    if (pid == 0)
    {
        int ev = execvp("/bin/ls", NULL);
        perror("");
    }
    else
    {
        wait(&pid);
    }

}


int main(int argc, char *argv[])
{
    if (pipe(pipefd) < 0)
    {
        perror("pipe");
        exit(1);
    }
    char **inputArray;
    char input[250];
    int inputSize=1;
    char* myString = "";
    // printf("welcome myshell ! by Gurkan Yakar \n");

    while (1)
    {
        printf("myshell>> ");
        fgets(input, 250, stdin); // read input
        for(int x=0; x<250; x++)
        {
            if(input[x] == ' '){
                inputSize++;
            }
        }
        //printf("inputSize: %d \n", inputSize);
        //printf("input: %s", input);
        char *token = strtok(input, " ");
        char *array[inputSize];
        int i = 0;
        while (token != NULL)
        {
            array[i++] = token;
            token = strtok(NULL, " ");
        }
        //for (i = 0; i < inputSize; ++i) 
        //   printf("%s\n", array[i]);


        if (strcmp(input, "ls\n") == 0)
        {
            lsFunction();
        }else if (strcmp(array[0], "cat") == 0 || strcmp(array[0], "cat\n")==0)
        {
            if(strcmp(array[0], "cat\n")==0){
                printf("eksik parametre girdiniz..!\n");
            }else{
                printf("cat:");
            }
            for (i = 1; i < inputSize; ++i){
                if(i == inputSize-1){
                    printf("%s", array[i]);
                }else{
                printf("%s ", array[i]);
                }
            } 
                
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
        }else if (strcmp(array[0], "writef") == 0 || strcmp(array[0], "writef\n") == 0) 
        {
            printf("%d",inputSize);
            if(inputSize!=3){
                printf("eksik parametre\n");
            }else{
                if(strcmp(array[1], "-f") == 0){
                    // file is exists
                    //array[2] = strtok(array[2], "\n");
                    char str[80];

                    strcpy(str, array[2]);
                    writefFunction(str);
                    /*
                    if (access(array[2], 0) == 0) {
                        // file exists; use pipe
                        printf("file is exists..!\n");
                    } else {
                        // file doesn't exist
                        printf("file is not exists..!\n");
                    }*/
                }
            }

            //printf("writef was hit\n");
        }else if (strcmp(input, "clear\n") == 0)
        {
            system("clear");
        }else
        {
            printf("unknown command\n");
        }

        inputSize = 1;
    }
    return 0;
}
