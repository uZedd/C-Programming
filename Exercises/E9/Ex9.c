#include <stdlib.h>
#include <stdio.h>

int main() {
    int valid;
    int answer;
    char extra;
    int result;
    int find_first(const unsigned int *array, unsigned int num);
    unsigned int numbers[20];
    for (int i = 0; i < 20; i++) {
        numbers[i] = rand() % 19 + 1;
        if (i == 19) {
            numbers[i] = 0;
        }
        printf("%d\n", numbers[i]);
    }


    do {
        printf("Input the number to look for or 0 to stop: ");
        valid = scanf("%d%c", &answer, &extra);
        if (valid != 2 || extra != '\n' || answer < 0 || answer > 20) {
            printf("Invalid input. Please try again.\n");
            if (valid != 2 || extra != '\n') {
                while (getchar() != '\n');
            }
        } else {
            result = find_first(numbers, answer);
            if (result == -1) {
                printf("Number wasn't found.\n");
            } else {
                printf("The first index of this number is: %d\n", result);
            }
        }
    } while (valid != 2 || extra != '\n' || answer != 0);
}

int find_first(const unsigned int *array, unsigned int num) {
    int found = 0;
    const unsigned int *original = array;
    do {
        if (*array == num && *array != 0) {
            found = array - original;
        } else if (*array == 0) {
            found = -1;
        }
        array++;
    } while (found == 0);

    return found;
}
