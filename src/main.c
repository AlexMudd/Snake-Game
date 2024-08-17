#include "../headers/global_vars.h"
#include "../headers/global_structs.h"
#include "../headers/inits.h"
#include "../headers/debug.h"
#include "../headers/thread_funcs.h"
#include "../headers/game.h"
#include "../headers/menu.h"

int main(){
    while(1){
        if(!menu()){
            endwin();
            return 0;
        }
        play();
    }
}