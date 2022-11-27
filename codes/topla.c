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
    char s[30];
    printf("Topla programina hosgeldiniz");
    read(3, s, 30);

    printf("deger = %s\n",s);

    return 0;
}