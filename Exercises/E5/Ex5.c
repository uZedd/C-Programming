#include <stdio.h>

int main () {
    int read_range(int min, int max);
    int choise;
    int number;
    int min = 1;
    int max = 6;

    do {
        number = read_range(min, max);
        if (number < max) {
            choise = number + 1;
        } else {
            choise = number;
        }
        printf("Your choise was %d, I chose %d.\n", number, choise);
        if (choise > number) {
            printf("I won, let's play again.\n");
        }
    } while (choise > number);

    printf("It was a tie, thank you for playing.");


}

int read_range(int min, int max) {
    int number;
    int valid;
    char extra;
    printf("Enter a number between 1 and 6: ");

    do {
        valid = scanf("%d%c", &number, &extra);
        if ((valid != 2) || extra != '\n' || (number < min) || (number > max)) {
            printf("Invalid number/input, try again: ");

            if (extra != '\n') {
                while (getchar() != '\n');
            }


        }
    } while (number > max || extra != '\n' || number < min || valid !=2);

    return number;

}