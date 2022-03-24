#ifndef SRC_ALIAS_H_
#define SRC_ALIAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "file_search.h"

#define N 30  // Vertical size of the window
#define M 106  // Horizontal size of the window

#define GAME_NAME "Alias!"

typedef struct {
    char **teams;
    char ***players;
    size_t *players_count;
    size_t teams_count;
    size_t *scores;
    Record **current_words;
    size_t current_words_count;
    size_t status;
} Game;

void print_rules();

char *str_input();
size_t input_teams_count();
char **input_teams(const size_t n);
size_t *init_players_counters(const size_t n);
char ***input_players(char **teams_, size_t *players_counts, const size_t n);

Game *init_game(char **teams_, size_t t_count, char ***players_, size_t *p_count);
void end_game(Game *game);
void destroy_game(Game *game);

void start_game(Game *game);

void print_game(Game *game);

#endif  // SRC_ALIAS_H_