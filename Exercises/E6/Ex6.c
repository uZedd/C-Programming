#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void roll_d10(void);
void roll_d6(void);

int main()
{
    srand((unsigned int)time(NULL));


    int answer = 0;
    char extra;
    do
    {
        printf("1) Roll D6\n2) Roll D10\n3) Exit\n");
        int valid = scanf("%d%c", &answer, &extra);
        if (valid == EOF)
        {
            printf("Input ended.\n");
            return 1;
        }

        if (valid != 2 || extra != '\n' || (answer != 1 && answer != 2 && answer != 3))
        {
            printf("Invalid input, try again.\n");
            answer = 0;
            if (valid != 2 || extra != '\n')
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                {
                }
            }
        }
        else if (answer == 1)
        {
            roll_d6();
        }
        else if (answer == 2)
        {
            roll_d10();
        }
    }
    while (answer != 3);

    printf("Exiting...");

    return 0;
}

void roll_d6(void)
{
    int number = rand() % 6 + 1;
    printf("I rolled %d from range 1 - 6.\n", number);
}

void roll_d10(void)
{
    int number = rand() % 10 + 1;
    printf("I rolled %d from range 1-10.\n", number);
}
