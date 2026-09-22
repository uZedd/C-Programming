#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int number;
    struct node *next;
} nnode;

int main() {
    int answerlength = 10;
    char answer[answerlength];
    nnode *head = NULL;
    nnode *tail = NULL;


    do {
        nnode *num;
        num = (nnode *) malloc(sizeof(nnode));
        num->next = NULL;
        printf("Give number: ");
        fgets(answer, answerlength, stdin);
        if (answer[strlen(answer) - 1] == '\n') {
            answer[strlen(answer) - 1] = '\0';
        }
        if (strcmp(answer, "end") != 0) {
            if (sscanf(answer, "%d", &num->number) != 1) {
                printf("invalid input.\n");
            } else {
                if (head == NULL) {
                    head = num;
                } else {
                    tail->next = num;
                }
                tail = num;
            }
        }
    } while (strcmp(answer, "end") != 0);

    nnode *temp;
    temp = head;
    do {
        printf("%d\n", temp->number);
        nnode *freeable = temp;
        temp = temp->next;
        free(freeable);
    } while (temp != NULL);

    return 0;
}
