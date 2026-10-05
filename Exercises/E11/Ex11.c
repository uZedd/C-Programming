#include <stdio.h>
#include <string.h>

int main() {
    int replace_char(char *s, const char *r);
    char string[100];
    char characters[100];
    printf("Enter the modifiable word/sentence: ");
    if (fgets(string, sizeof(string), stdin) == NULL) {
        return 1;
    }
    if (string[strlen(string) - 1] == '\n') {
        string[strlen(string) - 1] = '\0';
    }

    printf("Enter the character to modify and the character to modify it with: ");
    if (fgets(characters, sizeof(string), stdin) == NULL) {
        return 1;
    }
    if (characters[strlen(characters) - 1] == '\n') {
        characters[strlen(characters) - 1] = '\0';
    }

    int returning = replace_char(string, characters);

    if (returning > 0) {
        for (int i = 0; string[i] != '\0'; i++) {
            printf("%c", string[i]);
        }
        printf("\n");
        printf("Characters replaced: %d\n", returning);
    } else {
        printf("No characters replaced\n");
    }
    return 0;
}

int replace_char(char *s, const char *r) {
    if (strlen(r) != 2) {
        return 0;
    }
    int counter = 0;
    int index = 0;

    while (s[index] != '\0') {
        if (s[index] == *r && r[1] != '\0') {
            s[index] = r[1];
            counter++;
        }
        index++;
    }

    return counter;
}
