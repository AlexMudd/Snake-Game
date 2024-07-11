#include "../headers/main.h"

enum colors {
    color_player0,
    color_player1,
    color_player2,
    color_player3,
    color_wall,
    color_food,
    color_empty,
    color_player_singleplayer
};

int init_colors(){
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        return 0;
    }
    start_color();
    init_pair(color_wall, COLOR_WHITE, COLOR_WHITE);
    init_pair(color_food, COLOR_WHITE, COLOR_BLACK);
    init_pair(color_empty, COLOR_BLACK, COLOR_BLACK);
    init_pair(color_player0, COLOR_RED, COLOR_RED);
    init_pair(color_player1, COLOR_BLUE, COLOR_BLUE);
    init_pair(color_player2, COLOR_GREEN, COLOR_GREEN);
    init_pair(color_player3, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(color_player_singleplayer, COLOR_GREEN, COLOR_GREEN);
    clear();
    return 1;
}

void log_err(char* Error){
    FILE* logfile = fopen("../debug/errors.log", "a+");
    time_t mytime = time(0);
    struct tm* now = localtime(&mytime);
    fprintf(logfile, "\n%d.%d.%d %d:%d:%d\n%s\n", now->tm_mday, now->tm_mon, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec, Error);
    fclose(logfile);
}

int init_map(int max_x, int max_y){
    if(!init_colors()){ log_err("Can't init colors"); return 0; }
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
}

int play_singleplayer(){
    initscr();
    curs_set(0);
    noecho();
    init_map(100, 40);
    getch();
    endwin();
    return 1;
}


int main(){
    play_singleplayer();
    return 0;
}