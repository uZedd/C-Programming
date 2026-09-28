#include <stdio.h>

int read_integer(void);

int main() {

    float sum = 0;
    float average;
    int cur_num;

    int counter = 0;

    do {
        cur_num = read_integer();
        if (cur_num >= 0) {
            sum = sum + (float) cur_num;
            counter++;
        }
    } while (cur_num >= 0);
    if (counter > 0)
    {
        average = sum / (float) counter;
        printf("The average is %.3f", average);
    } else
    {
        printf("No numbers were entered.");
    }

}

int read_integer(void) {
    int number;
    char extra;
    int valid;
    printf("Enter positive numbers or negative to stop: ");
    do {
        valid = scanf("%d%c", &number, &extra);
        if (valid == EOF) {
            return -1;
        }

        if (valid != 2 || extra != '\n') {
            printf("Invalid input. Try again: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
            }

        }
    } while (valid != 2 || extra != '\n');

    return number;
}
