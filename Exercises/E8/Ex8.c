#include <stdio.h>
#include <stdlib.h>


int main() {
    void print_numbers(const int *array, int count);
    int amount = 15;
    int numbers[amount] = {};

    for (int i = 0; i < amount; i++) {
        numbers[i] = rand() % 100;
    }

    print_numbers(numbers, amount);

}

void print_numbers(const int *array, int count) {
    for (int i = 0; i < count; i++) {
        printf("|%8d|\n", *array);
        array++;
    }

}