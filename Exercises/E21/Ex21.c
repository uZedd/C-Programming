#include <stdio.h>
#include <string.h>

int main() {
    char filename[100];
    do {
        printf("give file name: ");
        if (fgets(filename, sizeof(filename), stdin) == NULL) {
            printf("Error reading filename\n");
            return 0;
        }
        if (filename[strlen(filename) - 1] == '\n') {
            filename[strlen(filename) - 1] = '\0';
        }
    } while (filename[0] == '\0');
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return 0;
    } else {
        int valid_start = 0;
        int valid_end = 0;
        int checksum = 0;
        int mask_count = 0;
        char maskstr[100];
        unsigned int mask;

        char row[128];
        while (!feof(f)) {
            if (fgets(row, sizeof(row), f) != NULL) {
                checksum = 0;
                valid_start = 0;
                valid_end = 0;
                mask_count = 0;
                for (int i = 0; row[i] != '\0' && row[i] != '\n'; i++) {
                    if (i == 0) {
                        valid_start = row[i] == '$';
                    }
                    if (i > 0 && row[i] == '*') {
                        valid_end = 1;
                    }
                    if (i > 0 && valid_start == 1 && valid_end == 0) {
                        checksum ^= row[i];
                    }
                    if (i > 0 && valid_end == 1 && row[i] != '*' && mask_count < sizeof(maskstr) - 1) {
                        maskstr[mask_count] = row[i];
                        mask_count++;
                    }
                }
                maskstr[mask_count] = '\0';

                if (valid_start == 1 && valid_end == 1 &&
                    sscanf(maskstr, "%2x", &mask) == 1) {
                    if (mask == checksum) {
                        printf("[OK] -- %s", row);
                    } else {
                        printf("[FAIL] -- %s", row);
                    }
                }
            }
        }
        fclose(f);
    }
}
