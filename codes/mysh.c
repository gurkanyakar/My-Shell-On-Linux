#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
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

void execFunction(char *command){
    int ev = 0;
    int pid = fork();
    if (pid == 0)
    { 
        write(pipefd[1], command, strlen(command));
        ev = execv("execx", NULL);
        perror("");
        close(pipefd[1]);
    }
    else
    { 
        //write(pipefd[1], filename, strlen(filename));
        wait(&ev);
    }
}

int isNumber(char s[])
{
    for (int i = 0; s[i]!= '\0'; i++)
    {
        if (isdigit(s[i]) == 0)
              return 0;
    }
    return 1;
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
            if(inputSize!=3){
                printf("eksik parametre girdiniz\n");
            }else{
                if(strcmp(array[1], "-f") == 0){
                    // file is exists
                    char str[80];

                    strcpy(str, array[2]);
                    writefFunction(str);
                }
            }
        }else if (strcmp(array[0], "execx") == 0 || strcmp(array[0], "execx\n") == 0) 
        {//myshell>> execx -t 3 wriref -f myfile
                    //array[2] = strtok(array[2],"\n");
            if(strcmp(array[1], "-t") == 0 && isNumber(array[2]) == 1 ){
                //writef
                
                if(strcmp(array[3], "writef") == 0 && strcmp(array[4], "-f") == 0 && inputSize == 6){
                    // file is exists
                    char str[80];

                    strcpy(str, array[2]);strcat(str, " ");
                    strcat(str, array[3]);strcat(str, " ");
                    strcat(str, array[4]);strcat(str, " ");
                    strcat(str, array[5]);
                    //printf("%s",str);
                    execFunction(str);
                }else if((strcmp(array[3], "cat\n") == 0 || strcmp(array[3], "cat") == 0 ) && inputSize >2){
                    // file is exists
                    char str[80];

                    strcpy(str, array[2]);
                    for (int q = 3; q < inputSize; q++)
                    {
                        strcat(str, " ");
                        strcat(str, array[q]);
                    }
                    printf("%s",str);
                    execFunction(str);
                }else if(strcmp(array[3], "ls\n") == 0  && inputSize == 3){
                    // file is exists
                    char str[80];

                    strcpy(str, array[2]);strcat(str, " ");
                    strcat(str, array[3]);//ls
                    printf("%s",str);
                    execFunction(str);
                }else if(strcmp(array[3], "bash\n") == 0  && inputSize == 3){
                    // file is exists
                    char str[80];

                    strcpy(str, array[2]);strcat(str, " ");
                    strcat(str, array[3]);//ls
                    printf("%s",str);
                    execFunction(str);
                }else if(strcmp(array[3], "exit\n") == 0  && inputSize == 3){
                    // file is exists
                    char str[80];

                    strcpy(str, array[2]);strcat(str, " ");
                    strcat(str, array[3]);//ls
                    printf("%s",str);
                    execFunction(str);
                }else if(strcmp(array[3], "clear\n") == 0  && inputSize == 3){
                    // file is exists
                    char str[80];

                    strcpy(str, array[2]);strcat(str, " ");
                    strcat(str, array[3]);//ls
                    printf("%s",str);
                    execFunction(str);
                }
            
            }else{
                printf("yanlis");
            }
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
