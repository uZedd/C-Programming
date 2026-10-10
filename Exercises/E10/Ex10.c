#include <stdio.h>
#include <string.h>


int main() {
    char stop[] = "stop";
    char string[100];

    do {
        printf("Enter a string: ");
        if (fgets(string, 100, stdin) == NULL)
        {
            return 0;
        }
        if (string[strlen(string) - 1] == '\n') {
            string[strlen(string) - 1] = '\0';
        }
        int length = strlen(string);
        printf("The length of the string is: %d\n", length);
    } while(strcmp(string, stop));

    printf("String was 'stop', stopping...");
}
