#include <stdio.h>

int main(void) {
    float bus_price;
    float taxi_price;
    float money;
    int answer;


    printf("Give the price of a bus ticket: ");
    scanf("%f", &bus_price);

    printf("Give the price of a taxi ticket: ");
    scanf("%f", &taxi_price);

    printf("How much money do you have?: ");
    scanf("%f", &money);

    while (money >= bus_price || money >= taxi_price) {
        printf("\nWhich one would you like to take?\n 1) Bus\n 2) Taxi\n");
        scanf("%d", &answer);

        if (answer == 1) {
            printf("\nYou chose bus.\n");
            if (money >= bus_price) {
                money = money - bus_price;
            } else {
                printf("You don't have enough money.\n");
            }
        } else if (answer == 2) {
            printf("\nYou chose taxi.\n");
            if (money >= taxi_price) {
                money = money - taxi_price;
            } else {
                printf("You don't have enough money.\n");
            }
        }
        printf("You have %.2f moneys left.\n", money);
    }
    printf("\nYou need to walk, bye.");

    return 0;
}
