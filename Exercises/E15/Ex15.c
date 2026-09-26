#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef struct menu_item_
{
    char name[50];
    double price;
} menu_item;

int main()
{
    struct menu_item_ items[40];

    int size = 100;
    int itemcount = 0;
    char filename[size];

    printf("Give file name: ");
    if (fgets(filename, size, stdin) == NULL)
    {
        fprintf(stderr, "Error fetching filename with fgets.");
    }
    if (filename[strlen(filename) - 1] == '\n')
    {
        filename[strlen(filename) - 1] = '\0';
    }

    FILE* f = fopen(filename, "r");

    if (f == NULL)
    {
        fprintf(stderr, "Error opening file \"%s\"\n", filename);
    } else
    {
        char row[128];
        while (!feof(f) && itemcount < 40)
        {
            if (fgets(row, sizeof(row), f) != NULL)
            {
                int read = sscanf(row, "%49[^;]; %lf", items[itemcount].name, &items[itemcount].price);
                if (read == 2)
                {
                    itemcount++;
                }
            }
        }
        fclose(f);

        printf("%-8s %s\n", "Price", "Item");
        printf("---------------------\n");

        for (int i = 0; i < itemcount; i++)
        {
            printf("%-8.2f %s\n", items[i].price, items[i].name);
        }
    }
    return 0;
}