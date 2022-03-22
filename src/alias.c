#include "data.h"
#include "file_search.h"

int main() {
    const char folder[] = "../database/";
    create_tmp_file_with_txt(folder);  // creating file with list of .txt files
    const int files_count = count_txt_files();
    char **files = read_tmp_file_with_txt(folder);
    remove_tmp_file_with_txt();
    printf("Total records: %d in %d files\n", count_all_records(files, files_count), files_count);
    for (int i = 0; i < files_count; i++) {
        FILE *file = fopen(files[i], "r");
        const int record_count = count_records(file);
        printf("----IN FILE %s - %d RECORDS----\n", files[i], record_count);
        for (int j = 1; j <= record_count; j++) {
            Record *record = read_record(file, j);
            printf("%s %s", record->eng_word, record->rus_word);
            free_record(record);
            if (j != record_count)
                printf("\n");
        }
        if (i != files_count - 1)
            printf("\n\n");
        if (file)
            fclose(file);
    }
    for (int i = 0; i < files_count; i++)
        free(files[i]);
    free(files);
    return 0;
}
