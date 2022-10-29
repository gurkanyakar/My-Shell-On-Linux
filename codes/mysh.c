#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char input[250];
    printf("welcome myshell ! by Gurkan Yakar \n");
    while (1) {
        printf("myshell>> ");
        fgets(input, 250, stdin); // read input
        printf("input: %s", input);
    }
}