#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int number;
    struct node *next;
} nnode;

int main() {
    int answerlength = 10;
    int number;
    char answer[answerlength];
    nnode *head = NULL;
    nnode *tail = NULL;




    do {
        char extra;
        nnode *num;

        printf("Give number: ");
        fgets(answer, answerlength, stdin);
        if (answer[strlen(answer) - 1] == '\n') {
            answer[strlen(answer) - 1] = '\0';
        }
        if (strcmp(answer, "end") != 0) {
            if (sscanf(answer, "%d%c", &number, &extra) != 1) {
                printf("invalid input.\n");
            } else {
                num = (nnode *) malloc(sizeof(nnode));
                if (num == NULL) {
                    printf("out of memory.\n");
                    break;
                }
                num->number = number;
                num->next = NULL;
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
    while (temp != NULL){
        printf("%d\n", temp->number);
        nnode *freeable = temp;
        temp = temp->next;
        free(freeable);
    }

    return 0;
}
