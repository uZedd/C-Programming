#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int number;
    struct node* next;
} nnode;

int main()
{
    int answerlength = 100;
    int running = 1;
    int number;
    char answer[answerlength];
    nnode* head = NULL;
    nnode* tail = NULL;

    do
    {
        char extra;
        nnode* num;
        int valid_input = 1;

        printf("Give number, end to stop: ");

        if (fgets(answer, answerlength, stdin) == NULL)
        {
            running = 0;
            valid_input = 0;
        }
        else if (strchr(answer, '\n') != NULL)
        {
            answer[strcspn(answer, "\n")] = '\0';
        }
        else
        {
            int c = getchar();
            if (c != '\n' && c != EOF)
            {
                while (c != '\n' && c != EOF)
                {
                    c = getchar();
                }
                printf("Input too long.\n");
                valid_input = 0;
            }
        }

        if (valid_input && strcmp(answer, "end") == 0)
        {
            running = 0;
        }

        if (valid_input && running)
        {
            if (sscanf(answer, "%d%c", &number, &extra) != 1)
            {
                printf("invalid input.\n");
            }
            else
            {
                num = (nnode*)malloc(sizeof(nnode));
                if (num == NULL)
                {
                    printf("out of memory.\n");
                    running = 0;
                }
                else
                {
                    num->number = number;
                    num->next = NULL;
                    if (head == NULL)
                    {
                        head = num;
                    }
                    else
                    {
                        tail->next = num;
                    }
                    tail = num;
                }
            }
        }
    }
    while (running);

    nnode* temp;
    temp = head;

    while (temp != NULL)
    {
        printf("%d\n", temp->number);
        nnode* freeable = temp;
        temp = temp->next;
        free(freeable);
    }

    return 0;
}
