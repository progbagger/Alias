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
    system("clear");  // ! WORKS ONLY IN UNIX-LIKE TERMINALS
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
    if (!err_no || result < 2 || result > 5) {
        while (!err_no || result < 2 || result > 5) {
            if (!err_no) {
                printf("It is not a number or a suitable number. Please, try again.\n");
            } else if (result < 2 || result > 5) {
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
Game *init_game(char **teams_, size_t t_count, char ***players_, size_t *p_count) {
    Game *game = malloc(sizeof(Game));
    game->teams = teams_;
    game->teams_count = t_count;
    game->scores = calloc(game->teams_count, sizeof(size_t));
    game->current_words = NULL;
    game->current_words_count = 0;
    game->status = 0;
    game->players = players_;
    game->players_count = p_count;
    return game;
}

// End game in case if teams wants to play again
void end_game(Game *game) {
    game->status = 0;
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
    game->status = 1;
}

// Printing game's info in terminal
void print_game(Game *game) {
    size_t uni_counter = game->teams_count;
    for (size_t i = 0; i < game->teams_count; i++) {
        uni_counter += game->players_count[i];
    }
    const char disp_teams_label[] = "Teams:", disp_score[] = "Score:";
    system("clear");  // ! WORKS ONLY IN UNIX-LIKE TERMINALS
    for (size_t i = 0; i < N; i++) {
        if (i == 0) {
            for (size_t j = 0; j < M / 2 - strlen(GAME_NAME) / 2; j++) {
                printf("*");
            }
            printf("%s", GAME_NAME);
            for (size_t j = 0; j < M / 2 - strlen(GAME_NAME) / 2 - 1; j++) {
                printf("*");
            }
        } else if (i == N - 1) {
            for (size_t j = 0; j < M - 1; j++) {
                printf("*");
            }
        } else if (i == 1) {
            printf("* %-20s %-20s", disp_teams_label, disp_score);
            for (size_t j = 0; j < M - strlen(GAME_NAME) - 31; j++) {
                printf(" ");
            }
            printf("*");
        } else if (i >= 2 && i < uni_counter) {
            size_t team_counter = 0;
            printf("* %-20s %-3lu", game->teams[team_counter], game->scores[team_counter]);
            team_counter++;
            i++;
            for (size_t j = 23; j < M - 1; j++)
                printf(" ");
            printf("*\n");
        } else {
            printf("*");
            for (size_t j = 0; j < M - 1 - 2; j++) {
                printf(" ");
            }
            printf("*");
        }
        printf("\n");
    }
    start_game(game);
    // for (size_t n = 0; n < N; n++) {
    //     for (size_t m = 0; m < M; m++) {
    //         if (n == 0) {
    //             if (m >= M / 2 - strlen(GAME_NAME) / 2 && m <= M / 2 + strlen(GAME_NAME) / 2 - 1) {
    //                 if (m == M / 2 - strlen(GAME_NAME) / 2)
    //                     printf(GAME_NAME);
    //             } else {
    //                 printf("*");
    //             }
    //         } else if (n == N - 1) {
    //             printf("*");
    //         } else if (m == 0 || m == M - 1) {
    //             printf("*");
    //         } else if (n == 2 && m >= M / 2 - strlen(disp_teams_label) / 2 && m < M / 2 + strlen(disp_teams_label) / 2) {
    //             if (m == M / 2 - strlen(disp_teams_label) / 2) {
    //                 printf("%s", disp_teams_label);
    //             }
    //         } else if (n == 3) {
    //             if (m == 1) {
    //                 printf(" ");
    //             } else if (m == 2) {
    //                 for (size_t i = 0; i < game->teams_count; i++) {
    //                     printf("%-20s", game->teams[i]);
    //                 }
    //                 for (size_t i = 0; i < 5 - game->teams_count; i++) {
    //                     for (size_t j = 1; j <= 20; j++)
    //                         printf(" ");
    //                 }
    //                 printf("   ");
    //             }
    //         } else if (n == 4) {
    //             if (m == 1) {
    //                 printf(" ");
    //             } else if (m == 2) {
    //                 for (size_t i = 0; i < game->teams_count; i++) {
    //                     printf("%-20lu", game->scores[i]);
    //                 }
    //                 for (size_t i = 0; i < 5 - game->teams_count; i++) {
    //                     for (size_t j = 1; j <= 20; j++)
    //                         printf(" ");
    //                 }
    //                 printf("   ");
    //             }
    //         } else
    //             printf(" ");
    //     }
    //     if (n != N - 1)
    //         printf("\n");
    // }
}
