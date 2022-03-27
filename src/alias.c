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

// strlen for unsigned char
size_t u_strlen(const unsigned char *str) {
    size_t result = 0, check = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (check) {
            check = 0;
            result++;
            continue;
        }
        if (str[i] > 127) {
            check = 1;
            continue;
        }
        result++;
    }
    return result;
}

// strcpy for unsigned char
unsigned char *u_strcpy(unsigned char *dest, const unsigned char *str) {
    size_t i = 0;
    for (; str[i] != '\0'; i++)
        dest[i] = str[i];
    dest[i] = '\0';
    return dest;
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
Game *init_game(const char *file_path) {
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
    game->words_file = fopen(file_path, "r");
    game->record_count = count_records(game->words_file);
    game->timer = 0.0;
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
    game->timer = 0.0;
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
        if (game->words_file)
            fclose(game->words_file);
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
    game->timer = ROUND_TIME;
    empty_words(game);
    set_up_random();
}

/*
    Function to handle next turn to next player
*/
void next_round(Game *game) {
    game->timer = ROUND_TIME;
    size_t i = 0, j = 0;
    size_t max_p_count = game->players_count[0];
    for (size_t k = 1; k < game->teams_count; k++)
        if (game->players_count[k] > max_p_count)
            max_p_count = game->players_count[k];
    short int check = 0;
    for (; j < max_p_count; j++) {
        for (; i < game->teams_count; i++) {
            if (j >= game->players_count[i])
                continue;
            if (game->players_status[i][j]) {
                check = 1;
                game->players_status[i][j] = 0;
                continue;
            }
            if (check) {
                check = 0;
                j = max_p_count;
                game->players_status[i][j] = 1;
                break;
            }
        }
        i = 0;
    }
    if (check)
        game->players_status[0][0] = 1;
    for (size_t k = 0; k < game->teams_count; k++)
        game->scores[k] += 100;
}

// Function to clear words queue
void empty_words(Game *game) {
    if (game->current_words) {
        for (size_t i = 0; i < game->current_words_count; i++)
            if (game->current_words[i])
                free_record(game->current_words[i]);
        free(game->current_words);
        game->current_words = NULL;
    }
    game->current_words_count = 0;
}

// Function which changes words
void next_word(Game *game) {
    Record **tmp = calloc(++(game->current_words_count), sizeof(Record*));
    /*
        ! Russian words and english transcription has more
        ! symbols in it and u_strlen returns shrinked amount
        ! of symbols so it is necessary to allocate safe amount
        ! of memory for these words
    */
    for (size_t i = 0; i < game->current_words_count - 1; i++) {
        tmp[i] = init_record();
        tmp[i]->eng_word = calloc(u_strlen(game->current_words[i]->eng_word) + 1, sizeof(unsigned char));
        tmp[i]->eng_word = u_strcpy(tmp[i]->eng_word, game->current_words[i]->eng_word);
        tmp[i]->transcription = calloc(u_strlen(game->current_words[i]->transcription) * 2 + 1, sizeof(unsigned char));
        tmp[i]->transcription = u_strcpy(tmp[i]->transcription, game->current_words[i]->transcription);
        tmp[i]->rus_word = calloc(u_strlen(game->current_words[i]->rus_word) * 2 + 1, sizeof(unsigned char));
        tmp[i]->rus_word = u_strcpy(tmp[i]->rus_word, game->current_words[i]->rus_word);
        free_record(game->current_words[i]);
    }
    if (game->current_words)
        free(game->current_words);
    game->current_words = tmp;
    game->current_words[game->current_words_count - 1] = read_record(game->words_file, random_record(game->record_count));
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
    const char words[] = "Words:", timer[] = "Time:";
    size_t shift = 0;
    if (game->current_words_count > N - 3)
        shift += (game->current_words_count - (N - 3));
    if (row == 1) {
        printf("    %s    %s %-4.1lf", words, timer, game->timer);
        for (int i = 0; i < (int) (M - 2 - strlen(words) - strlen(timer) - 5 - 4 - 4 - 30); i++)
            printf(" ");
    } else if (row - 2 < game->current_words_count) {
        printf("  ");
        if (row - 2 == game->current_words_count - 1)
            printf("> ");
        else
            printf("  ");
        printf(
            "%s [ %s ] - %s",
            game->current_words[row - 2 + shift]->eng_word,
            game->current_words[row - 2 + shift]->transcription,
            game->current_words[row - 2 + shift]->rus_word
        );
        for (int i = 0; i < (int) (M - 2 - 8 - 4 - 30 -
            u_strlen(game->current_words[row - 2 + shift]->eng_word) -
            u_strlen(game->current_words[row - 2 + shift]->transcription) -
            u_strlen(game->current_words[row - 2 + shift]->rus_word));
            i++
        ) {
            printf(" ");
        }
    } else {
        for (int i = 0; i < (int) (M - 30 - 2); i++)
            printf(" ");
    }
    printf(" *");
}

// Printing game's info in terminal
void print_game(Game *game) {
    size_t uni_counter = game->teams_count;
    for (size_t i = 0; i < game->teams_count; i++) {
        uni_counter += game->players_count[i];
    }
    // const char disp_teams_label[] = "Teams:", disp_score[] = "Score:";
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
    printf("\n");
}

// Function to handle game round
void game_round(Game *game) {
    start_game(game);
    double diff = 0.0;
    while (game->game_status) {
        if (game->timer < 0)
            end_game(game);
        if (game->game_status) {
            if (diff == 1.0) {
                next_word(game);
                diff = 0.0;
            }
            print_game(game);
            game->timer -= STEP;
            diff += STEP;
            usleep((useconds_t) SLEEP_TIME);
        } else {
            print_game(game);
            break;
        }
    }
}
