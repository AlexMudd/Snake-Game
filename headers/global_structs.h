#ifndef __GLOBALSTRUCTS_H__
#define __GLOBALSTRUCTS_H__

#define MAX_X 50
#define MAX_Y 40
#define TICK 100

enum colors {
    color_player_singleplayer = 1,
    color_wall,
    color_food,
    color_empty
};

enum directions {
    up,
    right,
    down,
    left
};

typedef struct{
    int x;
    int y;
}point;

typedef struct{
    enum directions dir;
    unsigned length;
    int new_tail;
    point* snake;
}player;

#endif