#include <stdio.h>
#include <string.h>

int main()
{
    int student;
    int grade = -1;
    int amount = 0;
    int extracted;
    char answer[100];
    char extra;

    while (amount < 1)
    {
        printf("Give the number of students (at least 1): ");
        if (fgets(answer, sizeof(answer), stdin) == NULL)
        {
            printf("Error in reading input!\n");
            return 1;
        }

        if (answer[strlen(answer) - 1] == '\n')
        {
            answer[strlen(answer) - 1] = '\0';
        }
        if (sscanf(answer, "%d%c", &extracted, &extra) != 1 || extracted < 1)
        {
            printf("Invalid input!\n");
        }
        else
        {
            amount = extracted;
        }
    }

    int students[amount];

    for (int i = 0; i < amount; i++)
    {
        students[i] = grade;
    }

    do
    {
        printf("\nEnter student number (%d - %d) or 0 to stop: ", 1, amount);
        if (fgets(answer, sizeof(answer), stdin) == NULL)
        {
            printf("Error in reading input!\n");
            return 1;
        }

        if (answer[strlen(answer) - 1] == '\n')
        {
            answer[strlen(answer) - 1] = '\0';
        }
        if (sscanf(answer, "%d%c", &extracted, &extra) != 1)
        {
            printf("Invalid student!\n");
            student = -1;
        }
        else
        {
            student = extracted;

            if (student > 0 && student <= amount)
            {
                do
                {
                    printf("Input the grade (0-5) for student %d or -1 to skip: ", student);

                    int result = scanf("%d", &grade);

                    if (result == EOF)
                    {
                        printf("Error in reading input!\n");
                        return 1;
                    }

                    int c;
                    while ((c = getchar()) != '\n' && c != EOF)
                    {
                    }

                    if (result != 1)
                    {
                        printf("Invalid grade!\n");
                        grade = -2;
                    }
                    else if (grade >= -1 && grade <= 5)
                    {
                        if (grade != -1)
                        {
                            students[student - 1] = grade;
                        }
                    }
                    else
                    {
                        printf("Invalid grade!\n");
                    }
                }
                while (grade < -1 || grade > 5);
            }
            else if (student != 0)
            {
                printf("Invalid student!\n");
            }
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
