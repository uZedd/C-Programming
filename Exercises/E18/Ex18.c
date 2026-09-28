#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    srand((unsigned int) time(NULL));

    int random;

    char response[100];
    int num = 0;
    int input_num = 0;
    char extra;
    int mask = 0x3f;

    while (num >= 0) {
        printf("Give number between 0 and 15: ");
        if (fgets(response, sizeof response, stdin) == NULL) {
            printf("Error reading input with fgets\n");
            return 0;
        }
        if (response[strlen(response) - 1] == '\n') {
            response[strlen(response) - 1] = '\0';
        }
        if (sscanf(response, "%d%c", &input_num, &extra) != 1 || (input_num > 15)) {
            printf("invalid input.\n\n");
        } else {
            num = input_num;
            if (num >= 0) {
                random = rand();
                printf("\nRandom number was: %d\nHexadecimal: %02x\n", random, random);

                random = random >> num;
                int result = random & mask;
                printf("Result of masking number was: %d\nHexadecimal: %02x\n\n", result, result);
            }
        }
    }

    return 0;
}
