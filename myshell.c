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
void writefFunc(char *filename){
    int ev = 0;
    int pid = fork();
    if (pid == 0)
    { 
        write(pipefd[1], filename, strlen(filename));
        ev = execv("writef", NULL);
        perror("");
        close(pipefd[1]);
    }
    else
    { 
        wait(&ev);
    }
}

void execFunc(char *command){
    int ev = 0;
    int pid = fork();
    if (pid == 0)
    { 
        write(pipefd[1], command, strlen(command));
        ev = execv("execx", NULL);
        perror("");
        close(pipefd[1]);
    }else{
        //wait(&ev);
        //sleep(1);
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

void bashFunc()
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

void lsFunc()
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

    char input[250];
    int size=1;
    // printf("welcome myshell ! by Gurkan Yakar \n");

    while (1)
    {
        printf("myshell>> "); // command line start
        fgets(input, 250, stdin); // input from user
        for(int x=0; x<250; x++)  // input size control
        {
            if(input[x] == ' '){ // if input has space
                size++;     // increase input size
            }
        }
        //printf("size: %d \n", size);
        //printf("input: %s", input);
        char *token = strtok(input, " "); // split input by space
        char *array[size]; // array for input
        int i = 0; // array index
        while (token != NULL) // split input by space
        {
            array[i++] = token; // add input to array
            token = strtok(NULL, " "); // split input by space
        }
        //for (i = 0; i < size; ++i) 
        //   printf("%s\n", array[i]);


        if (strcmp(input, "ls\n") == 0) // ls command no argument
        {
            lsFunc();
        }else if (strcmp(array[0], "cat") == 0 || strcmp(array[0], "cat\n")==0) // cat command
        {
            if(strcmp(array[0], "cat\n")==0){ // if cat command has no argument
                printf("You entered missing parameter input!\n");
            }else{
                printf("cat:");
            }
            for (i = 1; i < size; ++i){
                if(i == size-1){
                    printf("%s", array[i]);
                }else{
                printf("%s ", array[i]);
                }
            } 
                
        }
        else if (strcmp(input, "exit\n") == 0) // exit command no argument
        {
            exit(0);
        }
        else if (strcmp(input, "bash\n") == 0) // bash command no argument
        {
            bashFunc();
        }else if (strcmp(array[0], "writef") == 0 || strcmp(array[0], "writef\n") == 0) // writef command
        {
            if(size!=3){
                printf("You entered missing parameter input!\n"); // if writef command has no argument
            }else{ // 3 arguemnt 0 writef  1 -f  2 filename
                if(strcmp(array[1], "-f") == 0){ // check -f
                    // file is exists
                    char str[80];
                    strcpy(str, array[2]); // copy filename to str
                    writefFunc(str); 
                }
            }
        }else if (strcmp(array[0], "execx") == 0 || strcmp(array[0], "execx\n") == 0) // execx command
        {                                                                             //myshell>> [0]->execx [1]->-t [2]->3  [3]->wriref [4]->-f [5]->myfile
            if(strcmp(array[1], "-t") == 0 && isNumber(array[2]) == 1 ){ // check -t and time is number
                if(strcmp(array[3], "writef") == 0 && strcmp(array[4], "-f") == 0 && size == 6){  // check writef -f filename
                    char str[80];

                    strcpy(str, array[2]);strcat(str, " "); // copy time to str
                    strcat(str, array[3]);strcat(str, " "); // copy writef to str
                    strcat(str, array[4]);strcat(str, " "); // copy -f to str
                    strcat(str, array[5]); // copy filename to str
                    //printf("%s",str);
                    execFunc(str); // in function str will write to pipe
                }else if((strcmp(array[3], "cat\n") == 0 || strcmp(array[3], "cat") == 0 ) && size >3){ // check cat
                    char str[80];
                    strcpy(str, array[2]); // copy time to str
                    for (int q = 3; q < size; q++) 
                    {
                        strcat(str, " "); 
                        strcat(str, array[q]); // copy cat arguments to str
                    }
                    //printf("%s",str);
                    execFunc(str);
                }else if((strcmp(array[3], "ls\n") == 0 || strcmp(array[3], "ls") == 0 )&& size == 4){ // ls command no argument
                    char str[80];
                    strcpy(str, array[2]);strcat(str, " "); // copy time to str
                    strcat(str, array[3]);//ls
                    //printf("%s",str);
                    execFunc(str);
                }else if(strcmp(array[3], "bash\n") == 0  && size == 4){ // bash command no argument
                    char str[80];
                    strcpy(str, array[2]);strcat(str, " "); // copy time to str
                    strcat(str, array[3]);//bash
                    //printf("%s",str);
                    execFunc(str);
                }else if(strcmp(array[3], "exit\n") == 0  && size == 4){ // exit command no argument
                    char str[80];
                    strcpy(str, array[2]);strcat(str, " "); // copy time to str
                    strcat(str, array[3]);//exit
                    //printf("%s",str);
                    execFunc(str);
                }else if(strcmp(array[3], "clear\n") == 0  && size == 4){ // clear command no argument
                    char str[80];
                    strcpy(str, array[2]);strcat(str, " "); // copy time to str
                    strcat(str, array[3]);//clear
                    //printf("%s",str);
                    execFunc(str);
                }else{
                    printf("You entered missing parameter input!\n");
                }
            
            }else{
                printf("You entered missing parameter input!!\n");
            }
        }else if (strcmp(input, "clear\n") == 0) // clear command no argument
        {
            system("clear");
        }else if (strcmp(input, "help\n") == 0 || strcmp(input, "commands\n") == 0) // help command no argument
        {
            printf("ls - Displays the files in the directory\n");
            printf("bash - Runs bash program\n");
            printf("clear - Cleans everything in terminal\n");
            printf("exit - Allows to terminate the running program\n");
            printf("cat - Prints all text to the command line\n");
        }else
        {
            printf("Unknown command! Enter 'help' or 'commands' to see the commands available to you.\n");
        }

        size = 1;
    }
    return 0;
}
