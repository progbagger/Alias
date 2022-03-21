#ifndef SRC_DATA_H_
#define SRC_DATA_H_

#define EASY "../database/easyDatabase.txt"
#define PROGRAM "../database/programDatabase.txt"
#define USUALLY "../database/usuallyDatabase.txt"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct record {
    unsigned char *eng_word, *rus_word;
} Record;

Record *init_record();
void free_record(Record *record);
void skip_record(FILE *file);
Record *mem_record(FILE *file);
int count_records(FILE *file);
int count_all_records(const char **file_names, const int files_count);
Record *read_record(FILE *file, int pos);

#endif  // SRC_DATA_H_
