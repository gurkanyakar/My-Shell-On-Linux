#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
// 3 okuma 4 yazma

int main(void)
{
    //char sentence[100];
    int pid = getpid();
    int ppid = getppid();
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    //printf ( "Current local time and date: %s", asctime (timeinfo) );

    char s[30];
    read(3, s, 30);
    char *text = strtok(s, "\n");
    if (access(text, 0) == 0)
    {
        // file exists; use pipe
        printf("file is exists..!\n");
        FILE *myfile = fopen(text, "a");

        
        fprintf(myfile, "pid = %d ", pid);
        fprintf(myfile, "ppid = %d ", ppid);
        fprintf(myfile, "sistem saati = %s", asctime (timeinfo));
        fclose(myfile);
    }
    else
    {
        // file doesn't exist
        printf("file is not exists..!\n");
        FILE *myfile = fopen(text, "w");
        fprintf(myfile, "pid = %d ", pid);
        fprintf(myfile, "ppid = %d ", ppid);
        fprintf(myfile, "sistem saati = %s", asctime (timeinfo));
        fclose(myfile);
    }

        return 0;
}