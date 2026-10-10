#include <stdlib.h>
#include <stdio.h>

int main()
{
    int valid;
    int answer;
    char extra;
    int result;
    int find_first(const unsigned int* array, unsigned int num);
    unsigned int numbers[20];
    for (int i = 0; i < 20; i++)
    {
        numbers[i] = rand() % 20 + 1;
        if (i == 19)
        {
            numbers[i] = 0;
        }
        printf("%u\n", numbers[i]);
    }


    do
    {
        printf("Input the number to look for or 0 to stop: ");
        valid = scanf("%d%c", &answer, &extra);
        if (valid == EOF)
        {
            return 0;
        }
        if (valid != 2 || extra != '\n' || answer < 0)
        {
            printf("Invalid input. Please try again.\n");
            if (valid != 2 || extra != '\n')
            {
                int c;
                while ((c=getchar()) != '\n' && c != EOF);
            }
        }
        else if (answer != 0)
        {
            result = find_first(numbers, answer);
            if (result == -1)
            {
                printf("Number wasn't found.\n");
            }
            else
            {
                printf("The first index of this number is: %d\n", result);
            }
        }
    }
    while (valid != 2 || extra != '\n' || answer != 0);
}

int find_first(const unsigned int* array, unsigned int num)
{
    const unsigned int* original = array;
    while (*array != 0)
    {
        if (*array == num)
        {
            return array - original;
        }
        array++;
    }


    return -1;
}
