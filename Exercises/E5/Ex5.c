#include <stdio.h>
#include <stdlib.h>

int read_range(int min, int max);

int main()
{
    int choise;
    int number;
    int min = 1;
    int max = 6;

    for (int i = 0; i < 3; i++)
    {
        printf("Roll a die and enter your result.\n");
        number = read_range(min, max);

        if (number < max)
        {
            choise = number + 1;
        }
        else
        {
            choise = number;
        }

        printf("Your choice was %d, I chose %d.\n", number, choise);

        if (choise > number)
        {
            printf("I won!\n");
        }
        else
        {
            printf("It was a tie!\n");
        }
    }

    printf("I am too good, thank you for playing.\n");
}

int read_range(int min, int max)
{
    int number;
    int valid;
    char extra;
    printf("Enter a number between %d and %d: ", min, max);

    do
    {
        valid = scanf("%d%c", &number, &extra);
        if (valid == EOF)
        {
            printf("Input ended.\n");
            exit(1);
        }
        if ((valid != 2) || extra != '\n' || (number < min) || (number > max))
        {
            printf("Invalid number/input, try again: ");

            if (valid != 2 || extra != '\n')
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                {
                }
            }
        }
    }
    while (valid != 2 || number > max || extra != '\n' || number < min);

    return number;
}
