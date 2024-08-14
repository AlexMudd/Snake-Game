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

void* generate_food(void*);
void* get_key(void*);

#endif