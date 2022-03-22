#include "data.h"

// Initialization of one record
Record *init_record() {
    Record *result = malloc(sizeof(Record));
    result->eng_word = NULL;
    result->rus_word = NULL;
    return result;
}

// Cleaning allocated memory
void free_record(Record *record) {
    if (record) {  // ! in case of uninitialized record
        if (record->eng_word)
            free(record->eng_word);
        if (record->rus_word)
            free(record->rus_word);
        free(record);
    }
}

// Reading records without memorising them
void skip_record(FILE *file) {
    unsigned char c = fgetc(file);
    while (c != '\n')
        c = fgetc(file);
}

// Reading record into memory
Record *mem_record(FILE *file) {
    unsigned char *str1 = NULL, c = fgetc(file);
    size_t size = 0;
    Record *result = init_record();
    while (c < 160) {
        unsigned char *tmp = str1;
        str1 = realloc(tmp, (++size + 1) * sizeof(unsigned char));
        str1[size - 1] = c;
        c = fgetc(file);
    }
    if (str1) {  // ! Theoretically it is possible that str1 will be NULL
        // in case of unwilling space after last eng word
        unsigned char *tmp = str1;
        str1 = realloc(tmp, size * sizeof(unsigned char));
        str1[size - 1] = '\0';
    }
    result->eng_word = str1;
    size = 0;
    fseek(file, -1, SEEK_CUR);
    c = fgetc(file);
    unsigned char *str2 = NULL;
    while (c != '\n') {
        unsigned char *tmp = str2;
        str2 = realloc(tmp, (++size + 1) * sizeof(char));
        str2[size - 1] = c;
        c = fgetc(file);
    }
    if (str2)  // ! Like str1^^
        str2[size] = '\0';
    result->rus_word = str2;
    return result;
}

// Counting records in one file
size_t count_records(FILE *file) {
    fseek(file, 0, SEEK_SET);
    size_t result = 0;
    unsigned char c = fgetc(file);
    c = fgetc(file);
    if (file) {  // ! In case if this file will not be opened
        while (!feof(file)) {
            if (c == '\n')
                result++;
            c = fgetc(file);
        }
    }
    return result;
}

// Counting all the records in all .txt files
size_t count_all_records(char **file_names, const size_t files_count) {
    size_t result = 0;
    for (size_t i = 0; i < files_count; i++) {
        FILE *file = fopen(file_names[i], "r");
        if (file) {
            result += count_records(file);
            fclose(file);
        }
    }
    return result;
}

// Input one record from 
Record *read_record(FILE *file, size_t pos) {
    fseek(file, 0, SEEK_SET);
    Record *record = NULL;
    for (size_t i = 1; i < pos; i++)
        skip_record(file);
    record = mem_record(file);
    return record;
}
