#ifndef __MENU_H__
#define __MENU_H__

#include <ncurses.h>
#include <unistd.h>
#include "../headers/global_structs.h"
#include "../headers/inits.h"

extern int MAX_X;
extern int MAX_Y;
extern int TICK;

enum MenuSelect {
    PLAY,
    SETTINGS,
    EXIT,
    BACK,
    SMALL_MAP = 30,
    MEDIUM_MAP = 50,
    LARGE_MAP = 90,
    EASY_DIFFICULT = 200,
    MEDIUM_DIFFICULT = 100,
    HARD_DIFFICULT = 70
};


int menu();
void settings();

#endif