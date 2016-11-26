#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.c"
#include "goblin.c"
#include "weapons.c"
#include "chest.c"

int WIDTH = 25;
int HEIGHT = 48;

const char* up = "w";
const char* down = "s";
const char* left = "a";
const char* right = "d";

const char wall = 'X';
const char goblin = '*';
const char player = '@';
const char coin = '$';
const char door = '/';
const char chest = 'U';

int player_x = 1;
int player_y = 1;
int player_gold = 0;
int player_armor = 10;

int map[48][25] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 0, 3, 0, 0, 0, 0, 0, 3, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 3, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 6, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 6, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 6, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


int running = 1;

int main(){

    init_goblin_names();
    set_weapon("Hands");

    while(running == 1){
        printf("\n");

        /* get input, and check if we can move player*/

        char command[6];
        printf("> ");
        gets(command);

        /* player controls */
        map[player_y][player_x] = 0;
        if(strcmp(command, down) == 0){
            if(map[player_y + 1][player_x] == 0){
                player_y++;
            }
        }

        if(strcmp(command, up) == 0){
            if(map[player_y - 1][player_x] == 0){
                player_y--;
            }
        }

        if(strcmp(command, left) == 0){
            if(map[player_y][player_x - 1] == 0){
                player_x--;
            }
        }

        if(strcmp(command, right) == 0){
            if(map[player_y][player_x + 1] == 0){
                player_x++;
            }
        }

        if(strcmp(command, "collect") == 0){
            if(map[player_y][player_x + 1] == 4){
                map[player_y][player_x + 1] = 0;
                player_gold += 1;
            }

            else if(map[player_y][player_x - 1] == 4){
                map[player_y][player_x - 1] = 0;
                player_gold += 1;
            }

            else if(map[player_y + 1][player_x] == 4){
                map[player_y + 1][player_x] = 0;
                player_gold += 1;
            }

            else if(map[player_y - 1][player_x] == 4){
                map[player_y - 1][player_x] = 0;
                player_gold += 1;
            }
        }

        if(strcmp(command, "open") == 0){
            /* if coin */
            if(map[player_y][player_x + 1] == 5){
                map[player_y][player_x + 1] = 0;
            }

            else if(map[player_y][player_x - 1] == 5){
                map[player_y][player_x - 1] = 0;
            }

            else if(map[player_y + 1][player_x] == 5){
                map[player_y + 1][player_x] = 0;
            }

            else if(map[player_y - 1][player_x] == 5){
                map[player_y - 1][player_x] = 0;
            }

            /* if chest */
            if(map[player_y][player_x + 1] == 6){
                map[player_y][player_x + 1] = 0;

                if(rand() * 100 < 10){
                    set_weapon("Sword");
                }else{
                    player_gold += 15;
                }
            }

            else if(map[player_y][player_x - 1] == 6){
                map[player_y][player_x - 1] = 0;

                if(rand() * 100 < 10){
                    set_weapon("Sword");
                }else{
                    player_gold += 15;
                }
            }

            else if(map[player_y + 1][player_x] == 6){
                map[player_y + 1][player_x] = 0;

                if(rand() * 100 < 10){
                    set_weapon("Sword");
                }else{
                    player_gold += 15;
                }
            }

            else if(map[player_y - 1][player_x] == 6){
                map[player_y - 1][player_x] = 0;

                if(rand() * 100 < 10){
                    set_weapon("Sword");
                }else{
                    player_gold += 15;
                }
            }
        }

        /* clear */
        rl_screen_clear();

        

        /* then redraw*/
        printf("\x1b[30;47mGOLD: %i \n", player_gold);
        printf("ARMOR: %i / 1000\n", player_armor);
        printf("POWER: 1 (%s)\x1B[37;40m", weapon);

        for(int y = 0; y < HEIGHT; y++){
            printf("\n");
            for(int x = 0; x < WIDTH; x++){

                map[player_y][player_x] = 2;

                if(x <= (player_x + 5) && x >= (player_x - 5) && y <= (player_y + 5) && y >= (player_y - 5)){
                    if(map[y][x] == 1){
                        printf("%c", wall);
                    }

                    else if(map[y][x] == 2){
                        printf("\x1B[34m%c\x1B[37m", player);
                    }

                    else if(map[y][x] == 3){
                        printf("%c", goblin);
                    }

                    else if(map[y][x] == 4){
                        printf("%c", coin);
                    }

                    else if(map[y][x] == 5){
                        printf("%c", door);
                    }

                    else if(map[y][x] == 6){
                        printf("%c", chest);
                    }

                    else{
                        printf(" ");
                    }
                }
            }
        }

        if(map[player_y][player_x + 1] == 3 || map[player_y][player_x - 1] == 3 || map[player_y + 1][player_x] == 3 || map[player_y - 1][player_x] == 3){
            printf("\n%s the goblin is invoking a battle! Fight or Flee?", goblin_names[rand() % 16]);
            printf(" > ");

            char fight_command[5];
            gets(fight_command);

            if(strcmp(fight_command, "fight") == 0){
                printf("\x1B[33mYou killed the goblin! +2 gold\x1B[37;40m");
                player_gold += 2;
            }else if(strcmp(fight_command, "flee") == 0){
                printf("\x1B[33mYou have fled the goblin! You dropped some gold while running away! -2 gold\x1B[37;40m");
                player_gold -= 2;
            }else{
                printf("\x1B[33mThe goblin fled, after thieving 3 gold.\x1B[37;40m");
                player_gold -= 3;
            }

            if(map[player_y][player_x + 1] == 3) map[player_y][player_x + 1] = 0;
            if(map[player_y][player_x - 1] == 3) map[player_y][player_x - 1] = 0;
            if(map[player_y + 1][player_x] == 3) map[player_y + 1][player_x] = 0;
            if(map[player_y - 1][player_x] == 3) map[player_y - 1][player_x] = 0;
        }
    }

    return 0;
}
