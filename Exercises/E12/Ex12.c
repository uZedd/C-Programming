#include <stdio.h>
#include <string.h>

int main() {
    int count_words(const char *str, const char *word);
    char string[100];
    char word[100];

    do {
        printf("Input the haystack string: ");
        if (fgets(string, sizeof(string), stdin) == NULL) {
            return 0;
        }
        string[strcspn(string, "\n")] = '\0';
        printf("Input the needle string: ");
        if (fgets(word, sizeof(word), stdin) == NULL) {
            return 0;
        }
        word[strcspn(word, "\n")] = '\0';

        int value = count_words(string, word);
        printf("%d matches were found.\n", value);
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
