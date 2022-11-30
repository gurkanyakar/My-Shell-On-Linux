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
    int pid = getpid(); // process id
    int ppid = getppid();   // parent process id
    time_t rawtime; 
    struct tm * timeinfo; 
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    char s[30]; // input for pipe read
    read(3, s, 30); // read from pipe
    char *text = strtok(s, "\n"); // get filename from input
    if (access(text, 0) == 0) // file is exists
    {
        FILE *myfile = fopen(text, "a");
        fprintf(myfile, "pid = %d ", pid);
        fprintf(myfile, "ppid = %d ", ppid);
        fprintf(myfile, "sistem saati = %s", asctime (timeinfo));
        fclose(myfile);
    }
    else // file is not exists
    {
        FILE *myfile = fopen(text, "w");
        fprintf(myfile, "pid = %d ", pid);
        fprintf(myfile, "ppid = %d ", ppid);
        fprintf(myfile, "sistem saati = %s", asctime (timeinfo));
        fclose(myfile);
    }
        return 0;
}