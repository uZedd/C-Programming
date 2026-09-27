#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

bool passwordize(char* password, int password_capacity, const char* word);


int main()
{
    srand((unsigned int)time(NULL));


    int word_capacity = 32;

    char word[word_capacity];
    word[0] = '\0';


    while (strcmp(word, "stop") != 0)
    {
        printf("word please or stop, empty input doesn't count: ");
        if (fgets(word, word_capacity, stdin) == NULL)
        {
            printf("error during fgets.\n");
            strcpy(word, "stop");
        }
        else if (word[strlen(word) - 1] == '\n')
        {
            word[strlen(word) - 1] = '\0';
        }
        else
        {
            int c = getchar();
            if (c != '\n' && c != EOF)
            {
                printf("word is too long.\n");
                while (c != '\n' && c != EOF)
                {
                    c = getchar();
                }
                word[0] = '\0';
            }
        }

        if (strcmp(word, "stop") != 0 && strlen(word) > 0)
        {
            int word_size = strlen(word);

            int password_size = word_size * 2 + 2;

            char password[password_size];

            if (passwordize(password, password_size, word) == false)
            {
                printf("Error generating the password.\n");
            }
            else
            {
                printf("%s\n", password);
            }
        }
    }
    return 0;
}

// password generator function, used the range of 33-96 for the random ASCII characters.
bool passwordize(char* password, const int password_capacity, const char* word)
{
    int password_index = 0;

    if ((2 * strlen(word) + 2) > password_capacity)
    {
        return false;
    }

    while (*word != '\0')
    {
        password[password_index] = (char)(33 + rand() % 64);
        password_index++;
        password[password_index] = *word;
        password_index++;
        word++;
    }
    password[password_index] = (char)(33 + rand() % 64);
    password_index++;
    password[password_index] = '\0';
    return true;
}
