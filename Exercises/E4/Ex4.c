#include <stdio.h>

int main() {
    int read_integer(void);
    int numbers[100] = {};
    float sum = 0;
    float average;
    int cur_num;

    int counter = 0;

    do {
        cur_num = read_integer();
        if (cur_num >= 0) {
            numbers[counter] = cur_num;
            counter++;
        }
    } while (cur_num >= 0);
    for (int i = 0; i < counter; i++) {
        sum = sum + (float) numbers[i];
    }
    average = sum / (float) counter;
    printf("The average is %.2f", average);
}

int read_integer(void) {
    int number;
    char extra;
    int valid;
    printf("Enter positive numbers or negative to stop: ");
    do {
        valid = scanf("%d%c", &number, &extra);

        if (valid != 2 || extra != '\n') {
            printf("Invalid input. Try again: ");
            if (extra != '\n') {
                while (getchar() != '\n');
            }

        }
    } while (valid != 2 || extra != '\n');

    return number;
}
