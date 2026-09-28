#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct menu_item_ {
    char name[50];
    double price;
} menu_item;


int compare_price(const void *a, const void *b) {
    const menu_item *first = (const menu_item *) a;
    const menu_item *second = (const menu_item *) b;

    if (first->price > second->price) {
        return 1;
    } else if (first->price < second->price) {
        return -1;
    } else {
        return 0;
    }
}

int compare_name(const void *a, const void *b) {
    const menu_item *first = (const menu_item *) a;
    const menu_item *second = (const menu_item *) b;

    return strcmp(first->name, second->name);

}

int main() {
    struct menu_item_ items[40];

    int size = 100;
    int itemcount = 0;
    char filename[size];

    printf("Give file name: ");
    if (fgets(filename, size, stdin) == NULL) {
        fprintf(stderr, "Error fetching filename with fgets.");
    }
    if (filename[strlen(filename) - 1] == '\n') {
        filename[strlen(filename) - 1] = '\0';
    }

    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        fprintf(stderr, "Error opening file \"%s\"\n", filename);
    } else {
        char row[128];
        while (!feof(f) && itemcount < 40) {
            if (fgets(row, sizeof(row), f) != NULL) {
                int read = sscanf(row, "%49[^;]; %lf", items[itemcount].name, &items[itemcount].price);
                if (read == 2) {
                    itemcount++;
                }
            }
        }
        fclose(f);


        qsort(items, itemcount, sizeof(menu_item), compare_price);

        printf("%-8s %s\n", "Price", "Item");
        printf("---------------------\n");

        for (int i = 0; i < itemcount; i++) {
            printf("%-8.2f %s\n", items[i].price, items[i].name);
        }
    }
    return 0;
}
