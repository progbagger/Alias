#ifndef SRC_ALIAS_H_
#define SRC_ALIAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "defines.h"

#include "data.h"
#include "file_search.h"
#include "randomizer.h"

typedef struct {
    char **teams;
    char ***players;
    size_t *players_count;
    size_t teams_count;
    size_t *scores;
    Record **current_words;
    size_t current_words_count;
    size_t game_status;
    short int **players_status;
    size_t round;
    FILE *words_file;
    size_t record_count;
    double timer;
} Game;

/*
    Functions to correctly input teams names and
    players names
*/

char *str_input();
size_t u_strlen(const unsigned char *str);
unsigned char *u_strcpy(unsigned char *dest, const unsigned char *str);
size_t input_teams_count();
char **input_teams(const size_t n);
size_t *init_players_counters(const size_t n);
char ***input_players(char **teams_, size_t *players_counts, const size_t n);

/*
    Functions to manage game's settings
    during the game
*/

Game *init_game(const char *file_path);
void start_game(Game *game);
void next_word(Game *game);
void empty_words(Game *game);
void next_round(Game *game);
void end_game(Game *game);
void destroy_game(Game *game);

/*
    * Main function of the game
    * which rules everything
*/

void game_round(Game *game);

/*
    Functions to output game window
    with all necessary information
    into terminal
*/

void print_rules();
void print_teams(
    Game *game,
    const size_t row,
    const size_t uni,
    size_t *c_team,
    size_t *c_player
);
void print_words(Game *game, const size_t row);
void print_game(Game *game);

#endif  // SRC_ALIAS_H_
