#ifndef PLAGUE_H
#define PLAGUE_H
#define CELL_DEAD 0
#define CELL_ALIVE 1
#include "gameconfig.h"
#define GRIDWIDTH 40
#define GRIDHEIGHT 20
#define PLAGUE_SPRITE_INDEX 0xB9
#include "player.h"
/*
    Store information about the plague in question
*/
extern unsigned char conway_grid[100];

typedef struct
{
   char x;
   char y;
   char dx;
   char dy;
   unsigned char alive;
} virus_t;

void compute_generation();
unsigned char draw_virus(virus_t* virus, player_t* player, unsigned char spr_id);


void move_virus(virus_t* virus, player_t* player);




#endif