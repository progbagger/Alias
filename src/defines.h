#ifndef SRC_DEFINES_H_
#define SRC_DEFINES_H_

// * alias.h

#define N 30  // Vertical size of the window
#define M 120  // Horizontal size of the window

#define GAME_NAME "Alias!"

#define CLR_COMMAND "clear"  // ! UNIX-LIKE OS
// #define CLR_COMMAND "cls"    // ! WINDOWS

#define FILE_PATH "../database/words.txt"

#define SLEEP_TIME 200000
#define STEP (double) SLEEP_TIME / (double) 1000000
#define ROUND_TIME 5.0

// * file_search.h

#define TMP_FILE_WITH_TXT "data_files_names"

/*
    * Next strings need to be uncommented
    * depended on OS on which this program
    * compiles
*/

#define CMD1 "ls "                     // ! WORKS ONLY IN
#define CMD2 " | grep .txt > "         // ! UNIX-LIKE SYSTEMS

// #define CMD1 "dir /b "                 // ! WORKS ONLY IN
// #define CMD2 " | findstr \".txt\" > "  // ! WINDOWS


#endif  // SRC_DEFINES_H_
