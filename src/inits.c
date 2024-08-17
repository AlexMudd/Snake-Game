#include "../headers/inits.h"

int init_colors(){
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color");

        #ifdef DEBUG
            log_info("[-]The terminal does not support color");
        #endif

        return 0;
    }

    #ifdef DEBUG
        log_info("_____________________________________");
        log_info("[+]Colors Initiated 1/3");
    #endif

    start_color();
    init_pair(color_player_singleplayer, COLOR_GREEN, COLOR_GREEN);
    init_pair(color_wall, COLOR_WHITE, COLOR_WHITE);
    init_pair(color_food, COLOR_WHITE, COLOR_BLACK);
    init_pair(color_empty, COLOR_BLACK, COLOR_BLACK);
    init_pair(color_selected, COLOR_GREEN, COLOR_BLACK);
    clear();

    return 1;
}

int init_map(int max_x, int max_y){
    for(int i = 0; i <= max_x; i++){
        for(int j = 0; j <= max_y; j++){
            if(i == 0 || j == 0 || i == max_x || j == max_y){
                attron(COLOR_PAIR(color_wall));
                mvaddch(j, i, ' ');
                attroff(COLOR_PAIR(color_wall));
            }
        }
    }
    refresh();

    #ifdef DEBUG
        log_info("[+]Map Initiated 2/3");
    #endif

    return 1;
}

int init_player(player* snk){
    srand(time(0));
    snk->length = 1;
    snk->new_tail = 0;

    snk->snake = malloc(1*sizeof(point));
    snk->snake[0].x = 5 + rand() % (MAX_X - 5);
    snk->snake[0].y = 5 + rand() % (MAX_Y - 5);

    snk->dir = rand() % 4;
    
    #ifdef DEBUG
        log_info("[+]Player Initiated 3/3");
    #endif
    return 1;
}
