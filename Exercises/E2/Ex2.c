#include <stdio.h>

int main() {
    float incomes[12] = {};
    float taxes[12] = {};

    int length = sizeof(incomes) / sizeof(incomes[0]);

    float tax_rate;
    float big_tax_rate;
    int income_limit;

    float sum_of_incomes;

    printf("Input the basic tax rate: ");
    scanf("%f", &tax_rate);
    printf("Input the greater tax rate for income exceeding the limit: ");
    scanf("%f", &big_tax_rate);
    printf("Input the income limit: ");
    scanf("%d", &income_limit);

    for (int i = 0; i < length; i++) {
        printf("Input the income for month %d: ", i + 1);
        scanf("%f", &incomes[i]);
    }


    for (int i = 0; i < length; i++) {
        sum_of_incomes += incomes[i];
        float tax;

        if (sum_of_incomes <= income_limit) {
            tax = (tax_rate / 100 * incomes[i]);
        } else {
            tax = (big_tax_rate / 100 * incomes[i]);
        }
        taxes[i] = tax;
    }
    printf("%5s %12s %10s\n", "month", "income", "tax");

    for (int i = 0; i < 12; i++) {
        printf("%5d %10.2f %10.2f\n", i + 1, incomes[i], taxes[i]);
    }
}
