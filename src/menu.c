#include "../headers/menu.h"

int menu(){
    int menu_max_x, menu_max_y;
    int ready_to_play = 0;
    int exit = 0;
    enum MenuSelect select = PLAY;
    initscr();
    curs_set(0);
    noecho();
    init_colors();

    getmaxyx(stdscr, menu_max_y, menu_max_x);
    int centr_x = menu_max_x / 2;
    int centr_y = menu_max_y / 2;

    for(int i = 0; i < menu_max_x; i++){
        for(int j = 0; j < menu_max_y; j++){
            attron(COLOR_PAIR(color_empty));
            mvaddch(j, i, ' ');
            attroff(COLOR_PAIR(color_empty));
        }
    }

    attron(A_BOLD);
    mvprintw(centr_y - 3, centr_x - 4, "THE SNAKE");
    attroff(A_BOLD);

    mvprintw(centr_y - 1, centr_x - 2, "PLAY");
    mvprintw(centr_y + 1, centr_x - 4, "SETTINGS");
    mvprintw(centr_y + 3, centr_x - 2, "EXIT");

    attron(A_UNDERLINE);
    mvprintw(centr_y + 6, centr_x - 18, "Use wasd and space bar to choose...");
    attroff(A_UNDERLINE);

    refresh();

    TICK = EASY_DIFFICULT;
    MAX_X = menu_max_x * SMALL_MAP / 100;
    MAX_Y = menu_max_y * SMALL_MAP / 100;

    while(!ready_to_play && !exit){
        if(select == PLAY){

            attron(COLOR_PAIR(color_selected));
            mvprintw(centr_y - 1, centr_x - 2, "PLAY");
            attroff(COLOR_PAIR(color_selected));
            mvprintw(centr_y + 1, centr_x - 4, "SETTINGS");
            mvprintw(centr_y + 3, centr_x - 2, "EXIT");

            refresh();
            int k = getch();
            switch(k){
                case 's':
                    select = SETTINGS;
                break;

                case ' ':
                    ready_to_play = 1;
                break;
            }
        }

        if(select == SETTINGS){
            mvprintw(centr_y - 1, centr_x - 2, "PLAY");
            attron(COLOR_PAIR(color_selected));
            mvprintw(centr_y + 1, centr_x - 4, "SETTINGS");
            attroff(COLOR_PAIR(color_selected));
            mvprintw(centr_y + 3, centr_x - 2, "EXIT");

            refresh();
            int k = getch();
            switch(k){
                case 'w':
                    select = PLAY;
                break;

                case 's':
                    select = EXIT;
                break;

                case ' ':
                    //settings();
                break;
            }
        }

        if(select == EXIT){
            mvprintw(centr_y - 1, centr_x - 2, "PLAY");
            mvprintw(centr_y + 1, centr_x - 4, "SETTINGS");
            attron(COLOR_PAIR(color_selected));
            mvprintw(centr_y + 3, centr_x - 2, "EXIT");
            attroff(COLOR_PAIR(color_selected));

            refresh();
            int k = getch();
            switch(k){
                case 'w':
                    select = SETTINGS;
                break;
                
                case ' ':
                    exit = 1;;
                break;
            }
        }
    }
    return exit ? 0 : 1;
}

void settings(){

}
