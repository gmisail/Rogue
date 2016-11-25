#include <stdio.h>

void rl_screen_clear(){
    printf("\e[1;1H\e[2J");
}
