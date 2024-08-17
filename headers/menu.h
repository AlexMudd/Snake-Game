#ifndef __MENU_H__
#define __MENU_H__

#include <ncurses.h>
#include <unistd.h>
#include "../headers/global_structs.h"
#include "../headers/inits.h"

extern int MAX_X;
extern int MAX_Y;

enum MenuSelect {
    PLAY,
    SETTINGS,
    EXIT,
    BACK,
    SMALL_MAP = 30,
    MEDIUM_MAP = 50,
    LARGE_MAP = 90
};


int menu();
void settings();
//void border_settings();
//void speed_settings();

#endif