#ifndef __GLOBALSTRUCTS_H__
#define __GLOBALSTRUCTS_H__

enum colors {
    color_player_singleplayer = 1,
    color_wall,
    color_food,
    color_empty,
    color_selected
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