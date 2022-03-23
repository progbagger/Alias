#include "data.h"
#include "file_search.h"
#include "randomizer.h"
#include "alias.h"

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
    // show_files_contents(folder);  // * debug functon
    print_rules();
    const size_t teams_count = input_teams_count();
    char **teams = input_teams(teams_count);
    Game *game = init_game(teams, teams_count);
    print_game(game);
    destroy_game(game);
    return 0;
}
