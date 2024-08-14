#include "../headers/thread_funcs.h"


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