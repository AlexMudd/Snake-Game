#ifndef __GAME_H__
#define __GAME_H__

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../headers/global_structs.h"
#include "../headers/thread_funcs.h"
#include "../headers/inits.h"

extern point food;
extern player snk;
extern int score;
extern int need_food;
extern int quit;
extern int is_game_over;

extern int MAX_X;
extern int MAX_Y;
extern int TICK;

void draw_food();
void draw_snake();
void new_tail();
void move_snake();
void game_over();
void game();
int play();

#endif