#include "../headers/main.h"

#define MAX_X 50
#define MAX_Y 40
#define TICK 100

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
    int new_tail;
    point* snake;
}player;


int quit = 0;
int is_game_over = 0;
player snk[4];
int score[4] = {0, 0, 0, 0};
int need_food = 1;
point food;

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
    snk->new_tail = 0;

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

void draw_food(){
    attron(COLOR_PAIR(color_food));
    attron(A_BOLD);
    mvaddch(food.y, food.x, '*');
    attroff(COLOR_PAIR(color_food));
}

void new_tail(int num){
    snk[0].snake = (point*)realloc(snk[0].snake, (snk[0].length + 1)*sizeof(point));
    snk[0].length++;
}

void draw_snake(){
    //Draw head
    switch(snk[0].dir){
        case up:
            attron(COLOR_PAIR(snk[0].number));
            mvaddch(snk[0].snake[0].y - 1, snk[0].snake[0].x, ' ');
            attroff(COLOR_PAIR(snk[0].number));
        break;

        case down:
            attron(COLOR_PAIR(snk[0].number));
            mvaddch(snk[0].snake[0].y + 1, snk[0].snake[0].x, ' ');
            attroff(COLOR_PAIR(snk[0].number));
        break;
        
        case right:
            attron(COLOR_PAIR(snk[0].number));
            mvaddch(snk[0].snake[0].y, snk[0].snake[0].x + 1, ' ');
            attroff(COLOR_PAIR(snk[0].number));
        break;

        case left:
            attron(COLOR_PAIR(snk[0].number));
            mvaddch(snk[0].snake[0].y, snk[0].snake[0].x - 1, ' ');
            attroff(COLOR_PAIR(snk[0].number));
        break;
    }
    //Tail
    if(snk[0].new_tail == 0){
        //Draw empty at the end of the tail
        attron(COLOR_PAIR(color_empty));
        mvaddch(snk[0].snake[snk[0].length - 1].y, snk[0].snake[snk[0].length - 1].x, ' ');
        attroff(COLOR_PAIR(color_empty));
    }
    else{
        new_tail(snk[0].number);
        snk[0].new_tail = 0;
    }

    //Score bar
    for(int i = 0; i < getmaxx(stdscr); i++){
        mvaddch(MAX_Y + 5, i, ' ');
    }
    mvprintw(MAX_Y + 5, 0, "Your score: %d", score[0]);

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
    for(int i = snk[0].length - 1; i > 0; i--){
        snk[0].snake[i].x = snk[0].snake[i - 1].x;
        snk[0].snake[i].y = snk[0].snake[i - 1].y;
    }
    if(snk[0].dir == up){ snk[0].snake[0].y--; }
    if(snk[0].dir == down){ snk[0].snake[0].y++; }
    if(snk[0].dir == right){ snk[0].snake[0].x++; }
    if(snk[0].dir == left){ snk[0].snake[0].x--; }

    //Reaction to the wall
    if(snk[0].snake[0].x == 0 || snk[0].snake[0].x == MAX_X || snk[0].snake[0].y == 0 || snk[0].snake[0].y == MAX_Y){
        quit++;
        is_game_over++;
    }

    //Reaction to hit tail
    for(int i = 1; i < snk[0].length; i++){
        if(snk[0].snake[0].x == snk[0].snake[i].x && snk[0].snake[0].y == snk[0].snake[i].y){
            quit++;
            is_game_over++;
        }
    }

    //Reaction to the food
    if(snk[0].snake[0].x == food.x && snk[0].snake[0].y == food.y){
        need_food = 1;
        snk[0].new_tail = 1;
        score[0]++;
    }
}

void game_over(){
    usleep(3000000);
    wclear(stdscr);
    mvprintw(MAX_Y/2, MAX_X/2, "Game OVER");
    mvprintw(MAX_Y/2 + 1, MAX_X/2, "YOUR SCORE: %d", score[0]);
    mvprintw(MAX_Y/2 + 2, MAX_X/2, "PRESS ANY KEY...");
    refresh();
    getch();
}

void* get_key_singleplayer(void*){
    while(1){
        int k = getch();
        switch(k){
            case 'w':
                if(snk[0].dir != down) { snk[0].dir = up; }
                break;
            case 's':
                if(snk[0].dir != up) { snk[0].dir = down; }
                break;
            case 'd':
                if(snk[0].dir != left) { snk[0].dir = right; }
                break;
            case 'a':
                if(snk[0].dir != right) { snk[0].dir = left; }
                break;
            case 'q':
                quit++;
                break;              
        }
    }
}

void game_singleplayer(){
    while(!quit){
        draw_food();
        draw_snake();
        move_snake();
        refresh();
        usleep(TICK*1000);
    }
    if(is_game_over){ game_over(); }
}

int play_singleplayer(){
    pthread_t key_pid, food_pid;
    initscr();
    curs_set(0);
    noecho();
    init_map(MAX_X, MAX_Y);
    init_player(&snk[0], 4);
    pthread_create(&food_pid, NULL, generate_food, NULL);
    pthread_create(&key_pid, NULL, get_key_singleplayer, NULL);

    game_singleplayer();

    pthread_detach(key_pid);
    pthread_detach(food_pid);
    endwin();
    return 1;
}

int main(){
    play_singleplayer();
    return 0;
}