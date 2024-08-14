#include "../headers/main.h"

#define MAX_X 150
#define MAX_Y 40
#define TICK 100

//#define DEBUG

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


int quit = 0;
int is_game_over = 0;
player snk;
int score = 0;
int need_food = 1;
point food;

int init_colors(){
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        return 0;
    }
    start_color();
    init_pair(color_player_singleplayer, COLOR_GREEN, COLOR_GREEN);
    init_pair(color_wall, COLOR_WHITE, COLOR_WHITE);
    init_pair(color_food, COLOR_WHITE, COLOR_BLACK);
    init_pair(color_empty, COLOR_BLACK, COLOR_BLACK);
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

int init_player(player* snk){
    srand(time(0));
    snk->length = 1;
    snk->new_tail = 0;

    snk->snake = malloc(1*sizeof(point));
    snk->snake[0].x = 5 + rand() % (MAX_X - 5);
    snk->snake[0].y = 5 + rand() % (MAX_Y - 5);

    snk->dir = rand() % 4;
    
    #ifdef DEBUG
    FILE* logfile = fopen("../debug/errors.log", "a+");
    time_t mytime = time(0);
    struct tm* now = localtime(&mytime);
    fprintf(logfile, "\n%d.%d.%d %d:%d:%d\nHead: x %d, y %d, dir: %d\n", now->tm_mday, now->tm_mon, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec, snk->snake[0].x, snk->snake[0].y, snk->dir);
    fclose(logfile);
    #endif
}

void draw_food(){
    attron(COLOR_PAIR(color_food));
    attron(A_BOLD);
    mvaddch(food.y, food.x, '*');
    attroff(COLOR_PAIR(color_food));
}

void new_tail(){
    snk.snake = (point*)realloc(snk.snake, (snk.length + 1)*sizeof(point));
    snk.length++;
}

void draw_snake(){
    //Draw head
    switch(snk.dir){
        case up:
            attron(COLOR_PAIR(color_player_singleplayer));
            mvaddch(snk.snake[0].y - 1, snk.snake[0].x, ' ');
            attroff(COLOR_PAIR(color_player_singleplayer));
        break;

        case down:
            attron(COLOR_PAIR(color_player_singleplayer));
            mvaddch(snk.snake[0].y + 1, snk.snake[0].x, ' ');
            attroff(COLOR_PAIR(color_player_singleplayer));
        break;
        
        case right:
            attron(COLOR_PAIR(color_player_singleplayer));
            mvaddch(snk.snake[0].y, snk.snake[0].x + 1, ' ');
            attroff(COLOR_PAIR(color_player_singleplayer));
        break;

        case left:
            attron(COLOR_PAIR(color_player_singleplayer));
            mvaddch(snk.snake[0].y, snk.snake[0].x - 1, ' ');
            attroff(COLOR_PAIR(color_player_singleplayer));
        break;
    }
    //Tail
    if(snk.new_tail == 0){
        //Draw empty at the end of the tail
        attron(COLOR_PAIR(color_empty));
        mvaddch(snk.snake[snk.length - 1].y, snk.snake[snk.length - 1].x, ' ');
        attroff(COLOR_PAIR(color_empty));
    }
    else{
        new_tail();
        snk.new_tail = 0;
    }

    //Score bar
    for(int i = 0; i < getmaxx(stdscr); i++){
        mvaddch(MAX_Y + 5, i, ' ');
    }
    mvprintw(MAX_Y + 5, 0, "Your score: %d", score);

}

void* generate_food(void*){
    while(1){
        if(need_food){
            srand(time(0));
            food.x = 2 + rand() % (MAX_X - 3);
            food.y = 2 + rand() % (MAX_Y - 3);
            need_food = 0;
        }
    }
}

void move_snake(){
    for(int i = snk.length - 1; i > 0; i--){
        snk.snake[i].x = snk.snake[i - 1].x;
        snk.snake[i].y = snk.snake[i - 1].y;
    }
    if(snk.dir == up){ snk.snake[0].y--; }
    if(snk.dir == down){ snk.snake[0].y++; }
    if(snk.dir == right){ snk.snake[0].x++; }
    if(snk.dir == left){ snk.snake[0].x--; }

    //Reaction to the wall
    if(snk.snake[0].x == 0 || snk.snake[0].x == MAX_X || snk.snake[0].y == 0 || snk.snake[0].y == MAX_Y){
        quit++;
        is_game_over++;
    }

    //Reaction to hit tail
    for(int i = 1; i < snk.length; i++){
        if(snk.snake[0].x == snk.snake[i].x && snk.snake[0].y == snk.snake[i].y){
            quit++;
            is_game_over++;
        }
    }

    //Reaction to the food
    if(snk.snake[0].x == food.x && snk.snake[0].y == food.y){
        need_food = 1;
        snk.new_tail = 1;
        score++;
    }
}

void game_over(){
    usleep(3000000);
    wclear(stdscr);
    mvprintw(MAX_Y/2, MAX_X/2, "Game OVER");
    mvprintw(MAX_Y/2 + 1, MAX_X/2, "YOUR SCORE: %d", score);
    mvprintw(MAX_Y/2 + 2, MAX_X/2, "PRESS ANY KEY...");
    refresh();
    getch();
}

void* get_key(void*){
    while(1){
        int k = getch();
        switch(k){
            case 'w':
                if(snk.dir != down) { snk.dir = up; }
                break;
            case 's':
                if(snk.dir != up) { snk.dir = down; }
                break;
            case 'd':
                if(snk.dir != left) { snk.dir = right; }
                break;
            case 'a':
                if(snk.dir != right) { snk.dir = left; }
                break;
            case 'q':
                quit++;
                break;              
        }
    }
}

void game(){
    while(!quit){
        draw_food();
        draw_snake();
        refresh();
        move_snake();
        usleep(TICK*1000);
    }
    if(is_game_over){ game_over(); }
}

int play(){
    pthread_t key_pid, food_pid;

    initscr();
    curs_set(0);
    noecho();
    init_map(MAX_X, MAX_Y);
    init_player(&snk);

    pthread_create(&food_pid, NULL, generate_food, NULL);
    pthread_create(&key_pid, NULL, get_key, NULL);

    game();

    pthread_detach(key_pid);
    pthread_detach(food_pid);
    endwin();
    return 1;
}

int main(){
    play();
    return 0;
}