#include "../headers/game.h"

void new_tail(){
    snk.snake = (point*)realloc(snk.snake, (snk.length + 1)*sizeof(point));
    snk.length++;
}

void draw_food(){
    attron(COLOR_PAIR(color_food));
    attron(A_BOLD);
    mvaddch(food.y, food.x, '*');
    attroff(A_BOLD);
    attroff(COLOR_PAIR(color_food));
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
    need_food = 0;
    free(snk.snake);
    usleep(3000000);
    wclear(stdscr);
    mvprintw(MAX_Y/2, MAX_X/2, "Game OVER");
    mvprintw(MAX_Y/2 + 1, MAX_X/2, "YOUR SCORE: %d", score);
    mvprintw(MAX_Y/2 + 2, MAX_X/2, "PRESS ANY KEY...");
    refresh();
    getch();
}

void game(){
    quit = 0;
    is_game_over = 0;
    score = 0;
    need_food = 1;
    usleep(10000);
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
    clear();

    init_map(MAX_X, MAX_Y);
    init_player(&snk);

    pthread_create(&food_pid, NULL, generate_food, NULL);
    pthread_create(&key_pid, NULL, get_key, NULL);

    game();

    pthread_cancel(key_pid);
    pthread_cancel(food_pid);

    pthread_detach(key_pid);
    pthread_detach(food_pid);
    
    endwin();
    return 1;
}