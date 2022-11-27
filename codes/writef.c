#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    char string[8];
    printf("wrief.c is running");
    read(3, string, 8);
    printf("string = %s", string);
    return 0;
}