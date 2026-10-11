#include <stdio.h>
#include <string.h>

int main() {
    int name_size = 100;
    int count = 0;
    char file_name[name_size];
    int current_num;
    int high = -1;
    int low = 11;

    printf("Enter file name: ");

    if (fgets(file_name, name_size, stdin) == NULL) {
        return 1;
    }
    if (file_name[strlen(file_name) - 1] == '\n') {
        file_name[strlen(file_name) - 1] = '\0';
    }

    FILE *my_file;
    my_file = fopen(file_name, "r");
    if (my_file == NULL) {
        fprintf(stderr, "Unable to open file '%s'.\n", file_name);
        return 1;
    } else {
        while (fscanf(my_file, "%d", &current_num) == 1) {
            if (count == 0 || current_num > high) {
                high = current_num;
            }
            if (count == 0 || current_num < low) {
                low = current_num;
            }
            count++;
        }
        fclose(my_file);
        if (count > 0) {
            printf("%d numbers found. Highest was %d, lowest was %d.\n", count, high, low);
        } else {
            printf("0 numbers found.\n");
        }
    }
    return 0;
}
