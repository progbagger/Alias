#include "data.h"

// #define EASY "../database/easyDatabase.txt"
// #define PROGRAM "../database/programDatabase.txt"
// #define USUALLY "../database/usuallyDatabase.txt"

int main() {

    // list of all data files
    const char *files[] = {
        EASY,
        PROGRAM,
        USUALLY
    };

    // how many data files
    const int files_count = 3;

    // how many words in all data files
    int total_words_count = count_all_records(files, 3);

    FILE *file = fopen(EASY, "r");
    Record *record = read_record(file, 6);
    printf("%s %s\n", record->eng_word, record->rus_word);
    if (record)
        free(record);
    if (file)
        fclose(file);
    return 0;
}
