#include "alias.h"

// Function to input an string from stdin
char *str_input() {
    char *str = NULL, c = getchar();
    size_t size = 0;
    while (c != '\n') {
        char *tmp = str;
        str = realloc(tmp, (++size + 1) * sizeof(char));
        str[size - 1] = c;
        c = getchar();
    }
    if (str)
        str[size] = '\0';
    return str;
}

// Function to output rules and hello message
void print_rules() {
    system(CLR_COMMAND);
    printf("Welcome to the Alias game!\n\n");
    printf("In this game you will try to describe given words with without calling this word\n");
    printf("to your team. There can be up to 5 teams. Each player will try to describe\n");
    printf("given words only one time per round. Then commands can continue to play\n");
    printf("or finish the game and declare a winner.\n\n");
    printf("To start the game input number of teams from 2 to 5:\n");
}

// Function to input CORRECT teams count
size_t input_teams_count() {
    int result = 0;
    int err_no = scanf("%d", &result);
    while (getchar() != '\n') {}
    if (!err_no || result < 2 || result > 4) {
        while (!err_no || result < 2 || result > 4) {
            if (!err_no) {
                printf("It is not a number or a suitable number. Please, try again.\n");
            } else if (result < 2 || result > 4) {
                printf("%d teams can\'t play this game. Please, enter another number.\n", result);
            } else {
                printf("Unknown error. Please, try again.\n");
            }
            err_no = scanf("%d", &result);
            while (getchar() != '\n') {}
        }
    }
    return (size_t) result;
}

// Function to input teams names
char **input_teams(const size_t n) {
    const char *numerals[] = {
        "first",
        "second",
        "third",
        "forth",
        "fifth"
    };
    char **result = calloc(n, sizeof(char*));
    for (size_t i = 0; i < n; i++) {
        printf("Enter the name of the %s team:\n", numerals[i]);
        result[i] = str_input();
        if (!result[i]) {
            while (!result[i]) {
                printf("There can\'t be team with empty name. Please, enter suitable team name.\n");
                result[i] = str_input();
            }
        }
    }
    return result;
}

// Creation of array of players counters for each team
size_t *init_players_counters(const size_t n) {
    size_t *result = calloc(n, sizeof(size_t));
    return result;
}

// Function to input teams members
char ***input_players(char **teams_, size_t *players_counts, const size_t n) {
    const char *numerals[] = {
        "first",
        "second",
        "third",
        "forth",
        "fifth"
    };
    char ***players = calloc(n, sizeof(char**));
    for (size_t i = 0; i < n; i++) {
        int count = 0, err_no;
        printf("Enter players number for team %s:\n", teams_[i]);
        err_no = scanf("%d", &count);
        while (getchar() != '\n') {}
        if (!err_no || count < 2 || count > 5) {
            while (!err_no || count < 2 || count > 5) {
                if (!err_no) {
                    printf("It is not a number or a suitable number. Please, try again.\n");
                } else if (count < 2 || count > 5) {
                    printf("There can\'t be team with %d players. Please, enter suitable number.\n", count);
                } else {
                    printf("Unknown error. Please, try again.\n");
                }
                err_no = scanf("%d", &count);
                while (getchar() != '\n') {}
            }
        }
        players_counts[i] = (size_t) count;
        players[i] = calloc(players_counts[i], sizeof(char*));
        for (size_t j = 0; j < players_counts[i]; j++) {
            printf("Enter %s player name for team %s:\n", numerals[j], teams_[i]);
            players[i][j] = str_input();
            if (!players[i][j]) {
                while (!players[i][j]) {
                    printf("There can\'t be player with empty name. Please, enter suitable player's name.\n");
                    players[i][j] = str_input();
                }
            }
        }
    }
    return players;
}

// Create game
Game *init_game() {
    const size_t t_count = input_teams_count();
    char **teams = input_teams(t_count);
    size_t *players_counters = init_players_counters(t_count);
    char ***players = input_players(teams, players_counters, t_count);
    Game *game = malloc(sizeof(Game));
    game->teams = teams;
    game->teams_count = t_count;
    game->scores = calloc(game->teams_count, sizeof(size_t));
    game->current_words = NULL;
    game->current_words_count = 0;
    game->game_status = 0;
    game->players = players;
    game->players_count = players_counters;
    game->players_status = calloc(game->teams_count, sizeof(short int*));
    for (size_t i = 0; i < game->teams_count; i++)
        game->players_status[i] = calloc(game->players_count[i], sizeof(short int));
    game->round = 1;
    game->words_file = fopen(FILE_PATH, "r");
    if (!game->words_file) {
        printf("[ERROR] File couldn\'t opened for reading. Exiting.\n");
        destroy_game(game);
        game = NULL;
    }
    return game;
}

// End game in case if teams wants to play again
void end_game(Game *game) {
    game->game_status = 0;
    for (size_t i = 0; i < game->teams_count; i++)
        for (size_t j = 0; j < game->players_count[i]; j++)
            if (game->players_status[i][j])
                game->players_status[i][j] = 0;
}

// Destroy game
void destroy_game(Game *game) {
    if (game) {
        if (game->teams) {
            for (size_t i = 0; i < game->teams_count; i++) {
                if (game->teams[i])
                    free(game->teams[i]);
            }
            free(game->teams);
        }
        if (game->current_words) {
            for (size_t i = 0; i < game->current_words_count; i++) {
                if (game->current_words[i])
                    free_record(game->current_words[i]);
            }
            free(game->current_words);
        }
        if (game->players) {
            for (size_t i = 0; i < game->teams_count; i++) {
                if (game->players[i]) {
                    for (size_t j = 0; j < game->players_count[i]; j++) {
                        if (game->players[i][j])
                            free(game->players[i][j]);
                    }
                    free(game->players[i]);
                }
            }
            free(game->players);
        }
        if (game->players_status) {
            for (size_t i = 0; i < game->teams_count; i++) {
                if (game->players_status[i])
                    free(game->players_status[i]);
            }
            free(game->players_status);
        }
        if (game->scores)
            free(game->scores);
        if (game->players_count)
            free(game->players_count);
        free(game);
    }
}

/*
    idk what to write here... Hmm, this function
    starts the game :)
*/
void start_game(Game *game) {
    game->game_status = 1;
    game->players_status[0][0] = 1;
    set_up_random();
}

/*
    Function to handle next turn to next player
    and to switch words
*/
void next_round(Game *game) {
    if (game->game_status) {
        size_t current_player_i = 0, current_player_j = 0;
        short int check = 0;
        for (; current_player_i < game->teams_count; current_player_i++) {
            for (; current_player_j < game->players_count[current_player_i]; current_player_j++) {
                if (check) {
                    game->players_status[current_player_i][current_player_j] = 1;
                    current_player_i = game->teams_count;
                    check = 0;
                    break;
                }
                if (game->players_status[current_player_i][current_player_j]) {
                    check = 1;
                    game->players_status[current_player_i][current_player_j] = 0;
                }
            }
        }
        if (check) {
            game->players_status[0][0] = 1;
        }
    } else {
        printf("[ERROR] Game isn\'t started yet. Something went wrong.\n");
    }
}

// Printing left part of game window
void print_teams(
    Game *game,
    const size_t row,
    const size_t uni,
    size_t *c_team,
    size_t *c_player
) {
    const char d_teams[] = "Teams:", d_scores[] = "Scores:";
    printf("* ");
    if (row == 1) {
        printf("%-20s %-7s", d_teams, d_scores);
    } else if (row - 2 < uni) {
        if (!(*c_player)) {
            printf("%-20s %-7lu", game->teams[*c_team], game->scores[*c_team]);
            (*c_player)++;
            if (*c_team != game->teams_count)
                (*c_team)++;
        } else {
            if (game->players_status[(*c_team) - 1][(*c_player) - 1])
                printf("> ");
            else
                printf("  ");
            printf("%-26s", game->players[(*c_team) - 1][(*c_player) - 1]);
            if ((*c_player) != game->players_count[(*c_team) - 1])
                (*c_player)++;
            else
                (*c_player) = 0;
        }
    } else {
        for (size_t i = 0; i < 28; i++)
            printf(" ");
    }
}

// Printing right part of game window
void print_words(Game *game, const size_t row) {
    if (row) {
        for (size_t i = 0; i < M - 30 - 2; i++)
            printf(" ");
        printf(" *");
    }
    game->game_status = 1;
}

// Printing game's info in terminal
void print_game(Game *game) {
    size_t uni_counter = game->teams_count;
    for (size_t i = 0; i < game->teams_count; i++) {
        uni_counter += game->players_count[i];
    }
    // const char disp_teams_label[] = "Teams:", disp_score[] = "Score:";
    start_game(game);
    system(CLR_COMMAND);
    for (size_t i = 0; i < M / 2 - strlen(GAME_NAME) / 2; i++)
        printf("*");
    printf(GAME_NAME);
    for (size_t i = 0; i < M / 2 - strlen(GAME_NAME) / 2; i++)
        printf("*");
    printf("\n");
    size_t c_team = 0, c_player = 0;
    for (size_t i = 1; i < N - 1; i++) {
        print_teams(game, i, uni_counter, &c_team, &c_player);
        print_words(game, i);
        printf("\n");
    }
    for (size_t i = 0; i < M; i++)
        printf("*");
}
