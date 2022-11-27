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
    
    char str[80];

    strcpy(str, "fix");
    writefFunction(str);
    return 0;
}