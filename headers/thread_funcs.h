#ifndef __THREAD_H__
#define __THREAD_H__

#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include "../headers/global_structs.h"

extern int need_food;
extern point food;
extern player snk;
extern int quit;

extern int MAX_X;
extern int MAX_Y;
extern int TICK;

void* generate_food(void*);
void* get_key(void*);

#endif