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
}

// Function to input CORRECT teams count
size_t input_teams_count() {
    int result = 0;
    int err_no = scanf("%d", &result);
    while (getchar() != '\n') {}
    if (!err_no || result < 2) {
        while (!err_no || result < 2) {
            if (!err_no) {
                printf("It is not a number or a suitable number. Please, try again.\n");
            } else if (result < 2) {
                printf("%d players can\'t play this game. Please, enter another number.\n", result);
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

// Create game
Game *init_game(char **teams_, size_t t_count) {
    Game *game = malloc(sizeof(Game));
    game->teams = teams_;
    game->teams_count = t_count;
    game->scores = calloc(game->teams_count, sizeof(size_t));
    game->current_words = NULL;
    game->current_words_count = 0;
    game->status = 0;
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
        if (game->scores)
            free(game->scores);
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
    const char disp_teams_label[] = "Teams:";
    system("clear");  // ! WORKS ONLY IN UNIX-LIKE TERMINALS
    for (size_t n = 0; n < N; n++) {
        for (size_t m = 0; m < M; m++) {
            if (n == 0) {
                if (m >= M / 2 - strlen(GAME_NAME) / 2 && m <= M / 2 + strlen(GAME_NAME) / 2 - 1) {
                    if (m == M / 2 - strlen(GAME_NAME) / 2)
                        printf(GAME_NAME);
                } else {
                    printf("*");
                }
            } else if (n == N - 1) {
                printf("*");
            } else if (m == 0 || m == M - 1) {
                printf("*");
            } else if (n == 2 && m >= M / 2 - strlen(disp_teams_label) / 2 && m < M / 2 + strlen(disp_teams_label) / 2) {
                if (m == M / 2 - strlen(disp_teams_label) / 2) {
                    printf("%s", disp_teams_label);
                }
            } else if (n == 3) {
                if (m == 1) {
                    printf(" ");
                } else if (m == 2) {
                    for (size_t i = 0; i < game->teams_count; i++) {
                        printf("%-20s", game->teams[i]);
                    }
                    for (size_t i = 0; i < 5 - game->teams_count; i++) {
                        for (size_t j = 1; j <= 20; j++)
                            printf(" ");
                    }
                    printf("   ");
                }
            } else if (n == 4) {
                if (m == 1) {
                    printf(" ");
                } else if (m == 2) {
                    for (size_t i = 0; i < game->teams_count; i++) {
                        printf("%-20lu", game->scores[i]);
                    }
                    for (size_t i = 0; i < 5 - game->teams_count; i++) {
                        for (size_t j = 1; j <= 20; j++)
                            printf(" ");
                    }
                    printf("   ");
                }
            } else
                printf(" ");
        }
        if (n != N - 1)
            printf("\n");
    }
}
