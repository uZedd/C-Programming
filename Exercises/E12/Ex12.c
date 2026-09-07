#include <stdio.h>
#include <string.h>

int main() {
    int count_words(const char *str, const char *word);
    char string[100];
    char word[100];

    do {
        printf("Input the haystack string: ");
        fgets(string, sizeof(string), stdin);
        string[strlen(string) - 1] = '\0';
        printf("Input the needle string: ");
        fgets(word, sizeof(word), stdin);
        word[strlen(word) - 1] = '\0';

        if (strcmp(word, "stop") != 0) {
            int value = count_words(string, word);
            if (value == 0) {
                printf("No matches were found.\n");
            } else {
                printf("%d matches were found.\n", value);
            }
        }
    } while (strcmp(word, "stop") != 0);

    return 0;

}

int count_words(const char *str, const char *word) {
    int count = 0;
    char *found;

    if (*word == '\0') {
        return count;
    }
    do {
        found = strstr(str, word);
        if (found != NULL) {
            count++;
            str = found + strlen(word);
        }
    } while (found != NULL);
    return count;
}
