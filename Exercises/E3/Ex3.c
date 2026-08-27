#include <stdio.h>

int main()
{
    int student;
    int grade = -1;
    int amount = 0;

    while (amount < 1)
    {
        printf("Give the number of students (at least 1): ");
        scanf("%d", &amount);
    }


    int students[amount] = {};

    for (int i = 0; i < amount; i++)
    {
        students[i] = grade;
    }


    do
    {
        printf("\nEnter student number (%d - %d) or 0 to stop: ", 1, amount);
        if (scanf("%d", &student) != 1)
        {
            while (getchar() != '\n');
            printf("Invalid student!\n");
            student = -1;
        }
        else if (student > 0 && student <= amount)
        {
            do
            {
                printf("Input the grade for student %d: ", student);
                if (scanf("%d", &grade) != 1)
                {
                    while (getchar() != '\n');
                    printf("Invalid grade!\n");
                    grade = -2;
                }
                else if (grade >= -1 && grade <= 5)
                {
                    students[student - 1] = grade;
                }
                else
                {
                    printf("Invalid grade!\n");
                }
            }
            while (grade < -1 || grade > 5);
        } else
        {
            printf("Invalid student!\n");
        }
    }
    while (student != 0);
    printf("\n0 was inputted, printing.\n");

    printf("%-8s %-8s\n", "Student", "Grade");

    for (int i = 0; i < amount; i++)
    {
        if (students[i] == -1)
        {
            printf("%-8d %-8s\n", i + 1, "N/A");
        }
        else
        {
            printf("%-8d %-8d\n", i + 1, students[i]);
        }
    }
}
