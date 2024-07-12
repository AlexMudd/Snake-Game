#include "../headers/main.h"

#define MAX_X 100
#define MAX_Y 40
#define TICK 300

//#define DEBUG

enum colors {
    color_player0,
    color_player1,
    color_player2,
    color_player3,
    color_player_singleplayer,
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
    int number;
    enum directions dir;
    unsigned length;
    point* snake; 
}player;


int quit = 0;
int is_game_over = 0;
player snk[4];
int score[4] = {0, 0, 0, 0};

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

int init_player(player* snk, int num){
    srand(time(0));
    snk->number = num;
    snk->length = 1;

    snk->snake = malloc(1*sizeof(point));
    snk->snake[0].x = rand() % MAX_X;
    snk->snake[0].y = rand() % MAX_Y;

    while(1){
        snk->dir = rand() % 4;
        if(snk->dir = up || snk->snake[0].y > 2){ break; }
        if(snk->dir = down || snk->snake[0].y < MAX_Y - 2){ break; }
        if(snk->dir = right || snk->snake[0].x < MAX_X - 2){ break; }
        if(snk->dir = left || snk->snake[0].x > 2){ break; }
    }
    
    #ifdef DEBUG
    FILE* logfile = fopen("../debug/errors.log", "a+");
    time_t mytime = time(0);
    struct tm* now = localtime(&mytime);
    fprintf(logfile, "\n%d.%d.%d %d:%d:%d\nNum:%d, head: x %d, y %d, dir: %d\n", now->tm_mday, now->tm_mon, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec, snk->number, snk->snake[0].x, snk->snake[0].y, snk->dir);
    fclose(logfile);
    #endif
}

void draw_snake(player snk){
    //Draw head
    switch(snk.dir){
        case up:
            attron(COLOR_PAIR(snk.number));
            mvaddch(snk.snake[0].y - 1, snk.snake[0].x, ' ');
            attroff(COLOR_PAIR(snk.number));
        break;

        case down:
            attron(COLOR_PAIR(snk.number));
            mvaddch(snk.snake[0].y + 1, snk.snake[0].x, ' ');
            attroff(COLOR_PAIR(snk.number));
        break;
        
        case right:
            attron(COLOR_PAIR(snk.number));
            mvaddch(snk.snake[0].y, snk.snake[0].x + 1, ' ');
            attroff(COLOR_PAIR(snk.number));
        break;

        case left:
            attron(COLOR_PAIR(snk.number));
            mvaddch(snk.snake[0].y, snk.snake[0].x - 1, ' ');
            attroff(COLOR_PAIR(snk.number));
        break;
    }
    //Draw empty at the end of the tail
    attron(COLOR_PAIR(color_empty));
    mvaddch(snk.snake[snk.length - 1].y, snk.snake[snk.length - 1].x, ' ');
    attroff(COLOR_PAIR(color_empty));
}

void move_snake(player snk){
    for(int i = snk.length - 1; i > 0; i--){
        snk.snake[i].x = snk.snake[i - 1].x;
        snk.snake[i].y = snk.snake[i - 1].y;
    }
    if(snk.dir == up){ snk.snake[0].y--; }
    if(snk.dir == down){ snk.snake[0].y++; }
    if(snk.dir == right){ snk.snake[0].x++; }
    if(snk.dir == left){ snk.snake[0].x--; }

    if(snk.snake[0].x == 0 || snk.snake[0].x == MAX_X || snk.snake[0].y == 0 || snk.snake[0].y == MAX_Y){
        quit++;
        is_game_over++;
    }
}

void game_over(){
    wclear(stdscr);
    mvprintw(MAX_Y/2, MAX_X/2, "Game OVER");
    mvprintw(MAX_Y/2 + 1, MAX_X/2, "YOUR SCORE: ");
    refresh();
    getch();
}

void game(){
    while(!quit){
        draw_snake(snk[0]);
        move_snake(snk[0]);
        refresh();
        usleep(TICK*1000);
    }
    if(is_game_over){ game_over(); }
}

int play_singleplayer(){
    initscr();
    curs_set(0);
    noecho();
    init_map(MAX_X, MAX_Y);
    init_player(&snk[0], 4);
    game();
    endwin();
    return 1;
}


int main(){
    play_singleplayer();
    return 0;
}