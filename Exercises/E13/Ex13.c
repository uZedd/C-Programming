#include <stdio.h>
#include <string.h>

int main() {
    int char_size = 2;
    int name_size = 100;
    int count = 0;
    char file_name[name_size];
    int current_num;
    int high = -1;
    int low = 11;

    printf("Enter file name: ");

    fgets(file_name, name_size, stdin);
    if (file_name[strlen(file_name) - 1] == '\n') {
        file_name[strlen(file_name) - 1] = '\0';
    }

    FILE *my_file;
    my_file = fopen(file_name, "r");
    if (my_file == NULL) {
        fprintf(stderr, "Unable to open the file.\n");
    } else {
        while (!feof(my_file)) {
            if (fscanf(my_file, "%d", &current_num) == 1) {
                if (count == 0 || current_num > high) {
                    high = current_num;
                }
                if (count == 0 || current_num < low) {
                    low = current_num;
                }
                count++;
            } else {
                if (getc(my_file) == EOF) {
                    break;
                }
            }
        }
        fclose(my_file);
        printf("%d numbers found. Highest was %d, lowest was %d.", count, high, low);
    }
    return 0;
}
