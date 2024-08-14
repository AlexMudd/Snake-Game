#include "../headers/debug.h"

void log_info(char* Text){
    FILE* logfile = fopen("debug/logs.log", "a+");
    fprintf(logfile, "%s\n", Text);
    fclose(logfile);
}