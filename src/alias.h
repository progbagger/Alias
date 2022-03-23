#ifndef SRC_ALIAS_H_
#define SRC_ALIAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

#define N 30
#define M 106

#define GAME_NAME "Alias!"

typedef struct {
    char **teams;
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

Game *init_game(char **teams_, size_t t_count);
void end_game(Game *game);
void destroy_game(Game *game);

void start_game(Game *game);

void print_game(Game *game);

#endif  // SRC_ALIAS_H_