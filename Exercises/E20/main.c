#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "debug.h"

int main() {
    srand((unsigned int) time(NULL));

    int debug_level;
    int valid = 0;
    int temp;
    char extra;
    char response[100];

    do {
        printf("Insert debug level (0-4): ");
        if (fgets(response, sizeof(response),stdin) == NULL) {
            printf("Error reading from stdin.");
            return 0;
        }
        if (response[strlen(response) - 1] == '\n') {
            response[strlen(response) - 1] = '\0';
        }
        if (sscanf(response, "%d%c", &temp, &extra) != 1 || temp < 0 || temp > 4) {
            printf("Invalid input!");
            valid = 1;
        } else {
            debug_level = temp;
            valid = 0;
        }
    } while (valid == 1);
    set_debug_level(debug_level);

    for (int i = 1; i <= 5; i++) {
        int random = rand() % 5;
        dprintf(random, "Message %d\n", i);
    }

    return 0;
}
