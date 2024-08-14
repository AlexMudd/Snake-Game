#ifndef __INITS_H__
#define __INITS_H__

#include <ncurses.h>
#include <time.h>
#include "../headers/debug.h"
#include "../headers/global_structs.h"

extern int MAX_X;
extern int MAX_Y;
extern int TICK;

int init_colors();
int init_map(int max_x, int max_y);
int init_player(player* snk);

#endif