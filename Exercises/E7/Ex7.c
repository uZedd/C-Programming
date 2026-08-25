#include <stdio.h>
#include <stdbool.h>

int main() {
    bool read_positive(int *x);
    int guess;
    int counter = 0;
    int money;
    int check;
    do {
        printf("Guess how much money i have!\n");
        check = read_positive(&guess);
        if (check == 0) {
            counter++;
        } else {
            money = (guess * 2) + 20;
            printf("I have %d money! You were wrong.\n", money);
        }
    } while (counter < 3);
    printf("I got tired good bye.");
}

bool read_positive(int *x) {
    int temp;
    char extra;
    int valid;
    printf("Input a positive integer: ");


    valid = scanf("%d%c", &temp, &extra);
    if (valid != 2 || extra != '\n' || temp < 0) {
        printf("Invalid input\n");
        if (valid != 2 || extra != '\n') {
            while (getchar() != '\n');
        }
        return false;
    } else {
        *x = temp;
        return true;
    }
}
