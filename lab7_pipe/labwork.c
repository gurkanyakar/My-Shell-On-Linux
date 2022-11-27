#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
int pipefd[2];
int menu(void)
{
    int reply;

    puts("\n1- TOPLA");
    puts("2- CARP");
    puts("3- CIKIS");
    scanf("%d", &reply);

    return reply;
}
void Topla()
{
    printf("Topla fonksiyonu cagirildi");
    int ev = 0;
    int pid = fork();
    if (pid == 0)
    { // child process
        //printf("Child process");
        ev = execve("topla", NULL, NULL);
        perror("");
    }
    else
    { // main process
        //printf("Main process");
        // wait(&ev);
        char s[10];
        do
        {
            scanf("%s", s);
            write(pipefd[1], s, strlen(s));
        } while (strcmp(s, "topla") != 0);

        // fgets(s, 10, stdin);
        wait(&ev);
    }
}
void Carp()
{
    printf("Carp fonksiyonu cagirildi");
    int ev = 0;
    int pid = fork();
    if (pid == 0)
    { // child process
        //printf("Child process");
        ev = execve("carp", NULL, NULL);
        perror("");
    }
    else
    { // main process
        //printf("Main process");
        // wait(&ev);
        char s[10];
        do
        {
            scanf("%s", s);
            write(pipefd[1], s, strlen(s));
        } while (strcmp(s, "carp") != 0);

        // fgets(s, 10, stdin);
        wait(&ev);
    }
}
int main(void)
{
    if (pipe(pipefd) < 0)
    {
        perror("pipe");
        exit(1);
    }
    int choice;
    while (1)
    {
        choice = menu();

        if (choice == 1)
        {
            puts("\nTOPLAMA ISLEMI YAPILIYOR");
            Topla();
        }
        else if (choice == 2)
        {
            puts("\nCARPMA ISLEMI YAPLIYOR");
            Carp();
        }
        else if (choice == 3)
        {
            puts("\nPROGRAMDAN CIKIS YAPILIYOR\n");
            exit(0);
        }
        else
        {
            puts("\nYANLIS DEGER GIRDINIZ");
        }
    }
    return 0;
}