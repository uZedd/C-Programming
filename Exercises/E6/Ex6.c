#include <stdio.h>
#include <stdlib.h>

int main() {
    void roll_d10();
    void roll_d6();
    int answer;
    char extra;
    do {
        printf("1) Roll D6\n2) Roll D10\n3) Exit\n");
        int valid = scanf("%d%c", &answer, &extra);

        if (valid != 2 || extra != '\n' || (answer != 1 && answer != 2 && answer != 3)) {
            printf("Invalid input, try again.\n");
            if (valid != 2 || extra != '\n') {
                while (getchar() != '\n');
            }
        } else if (answer == 1) {
            roll_d6();
        } else if (answer == 2) {
            roll_d10();
        }
    } while (answer != 3);

    printf("Exiting...");
}

void roll_d6() {
    int number = rand() % 6 + 1;
    printf("I rolled %d from range 1 - 6.\n", number);
}

void roll_d10() {
    int number = rand() % 10 + 1;
    printf("I rolled %d from range 1-10.\n", number);
}
