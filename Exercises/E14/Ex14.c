#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int size = 100;
    int linecount = 0;
    char lines[100][82];
    char filename[size];

    printf("Give file name: ");
    if (fgets(filename, size, stdin) == NULL)
    {
        fprintf(stderr, "Failed to fetch the filename.\n");
        return 1;
    }
    if (filename[strlen(filename) - 1] == '\n')
    {
        filename[strlen(filename) - 1] = '\0';
    }

    FILE* f = fopen(filename, "r");

    if (f == NULL)
    {
        fprintf(stderr, "Error opening file\n");
    }
    else
    {
        while (linecount < size && fgets(lines[linecount], sizeof(lines[linecount]), f) != NULL)
        {
            lines[linecount][strcspn(lines[linecount], "\n")] = '\0';
            linecount++;
        }
        fclose(f);

        for (int i = 0; i < linecount; i++)
        {
            for (int j = 0; j < strlen(lines[i]); j++)
            {
                lines[i][j] = toupper((unsigned char)lines[i][j]);
            }
        }

        f = fopen(filename, "w");
        if (f == NULL)
        {
            fprintf(stderr, "Error opening file\n");
        }
        else
        {
            for (int i = 0; i < linecount; i++)
            {
                fprintf(f, "%s\n", lines[i]);
            }
            fclose(f);
        }

    }
}
