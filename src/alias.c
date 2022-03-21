#include "data.h"

// #define EASY "../database/easyDatabase.txt"
// #define PROGRAM "../database/programDatabase.txt"
// #define USUALLY "../database/usuallyDatabase.txt"

int main() {
    const char *file_names[] = { EASY, PROGRAM, USUALLY };
    const int files_count = 3;
    Record *record = NULL;
    for (int i = 0; i < files_count; i++) {
        FILE *file = fopen(file_names[i], "r");
        int words_count = count_records(file);
        for (int i = 1; i <= words_count; i++) {
            record = read_record(file, i);
            printf("%s %s", record->eng_word, record->rus_word);
            free(record);
            if (i != words_count)
                printf("\n");
        }
        fclose(file);
        if (i != files_count - 1)
            printf("\n\n");
    }
    return 0;
}
