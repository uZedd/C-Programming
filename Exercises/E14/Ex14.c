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
    if (fgets(filename, size, stdin) == NULL )
    {
        fprintf(stderr, "failed to fetch the filename.\n");
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
        while (!feof(f) && linecount < size)
        {
            if (fgets(lines[linecount], 82, f) != NULL)
            {
                if (lines[linecount][strlen(lines[linecount]) - 1] == '\n')
                {
                    lines[linecount][strlen(lines[linecount]) - 1] = '\0';
                }


                linecount++;
            }
        }
        fclose(f);

        for (int i = 0; i < linecount; i++)
        {
            for (int j = 0; j < strlen(lines[i]); j++)
            {
                lines[i][j] = toupper(lines[i][j]);
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
