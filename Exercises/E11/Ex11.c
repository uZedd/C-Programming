#include <stdio.h>
#include <string.h>

int main() {
    int replace_char(char *s, const char *r);
    char string[100];
    char characters[3];
    printf("Enter the modifiable word/sentence: ");
    fgets(string, sizeof(string), stdin);

    printf("Enter the character to modify and the character to modify it with: ");
    fgets(characters, sizeof(characters), stdin);

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
