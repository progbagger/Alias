#include "data.h"

// Initialization of one record
Record *init_record() {
    Record *result = malloc(sizeof(Record));
    result->eng_word = NULL;
    result->rus_word = NULL;
    return result;
}

// Reading records without memorising them
void skip_record(FILE *file) {
    char str[100];
    fgets(str, 100, file);
}

// Reading record into memory
Record *mem_record(FILE *file) {
    unsigned char *str = NULL, c = fgetc(file);
    int size = 0;
    Record *result = init_record();
    while (c < 160) {
        unsigned char *tmp = str;
        str = realloc(tmp, (++size + 1) * sizeof(unsigned char));
        str[size - 1] = c;
        c = fgetc(file);
    }
    if (str) {
        // in case of unwilling space after last eng word
        unsigned char *tmp = str;
        str = realloc(tmp, size * sizeof(unsigned char));
        str[size - 1] = '\0';
    }
    result->eng_word = str;
    str = NULL;
    size = 0;
    fseek(file, -1, SEEK_CUR);
    c = fgetc(file);
    while (c != '\n') {
        unsigned char *tmp = str;
        str = realloc(tmp, (++size + 1) * sizeof(char));
        str[size - 1] = c;
        c = fgetc(file);
    }
    if (str)
        str[size] = '\0';
    result->rus_word = str;
    return result;
}

// Counting records in one file
int count_records(FILE *file) {
    fseek(file, 0, SEEK_SET);
    int result = 0;
    unsigned char c = fgetc(file);
    c = fgetc(file);
    if (file) {
        while (!feof(file)) {
            if (c == '\n')
                result++;
            c = fgetc(file);
        }
    }
    return result;
}

// Counting all the records in all .txt files
int count_all_records(const char **file_names, const int files_count) {
    int result = 0;
    for (int i = 0; i < files_count; i++) {
        FILE *file = fopen(file_names[i], "r");
        result += count_records(file);
        fclose(file);
    }
    return result;
}

// Input one record from 
Record *read_record(FILE *file, int pos) {
    fseek(file, 0, SEEK_SET);
    Record *record = NULL;
    for (int i = 1; i < pos; i++)
        skip_record(file);
    record = mem_record(file);
    return record;
}
