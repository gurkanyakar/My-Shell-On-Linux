#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int strtoint( char* charnums)
{
 int number=0;
 int index=0;
 while(charnums[index])
 {
    if(('0'<=charnums[index]) && (charnums[index]<='9'))
    {

    if(!number)
        number= ( (int) charnums[index]) - 48;
    else
    {
        number = (number *= 10) + ((int) charnums[index] - 48);
    }
    index++;
         }
         else
         {
            number=1;
            //printf("\nGecersiz islem");
            break;
         }
 }
 return number;
}

// 3 okuma 4 yazma

int main(int argc, char *argv[])
{
    int toplam = 1;
    char s[10];
    printf("Carp programina hosgeldiniz");

    do{
            //scanf("%s",s);
            read(3, s, 10);
            printf("deger = %s\n",s);
            toplam *= strtoint(s);
            printf("Toplam = %d\n", toplam);
        }while(strcmp(s,"carp")!= 0);
        //printf("Toplam = %d", toplam);
    //write(pipefd[1], s, strlen(s));
    

    return 0;
}