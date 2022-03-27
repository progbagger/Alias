#include "data.h"
#include "file_search.h"
#include "randomizer.h"
#include "alias.h"
#include "defines.h"

/*
    TODO: Function to sort and clarify contents
    TODO: of given file

    TODO: Function to sort and clarify ALL FILES
    TODO: at specified folder

    TODO: Realize more fast and less memory usable
    TODO: mathod of searching by strokes in file
*/

int main() {
    // const char folder[] = "../database/";
    const char file_path[] = "../database/words.txt";
    // show_files_contents(folder);  // * debug functon
    print_rules();
    Game *game = init_game(file_path);
    for (size_t i = 0; i < 4; i++) {
        game_round(game);
        next_round(game);
    }
    destroy_game(game);
    return 0;
}
