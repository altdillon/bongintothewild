#ifndef PLAGUE_H
#define PLAGUE_H
#define CELL_DEAD 0
#define CELL_ALIVE 1
#include "gameconfig.h"
#define GRIDWIDTH 40
#define GRIDHEIGHT 20
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
   unsigned char time_alive; // time that the virus gets to live for
} virus_t;

void compute_generation();
unsigned char draw_virus(virus_t* virus, player_t* player, unsigned char spr_id);


void move_virus(virus_t* virus, player_t* player,unsigned char nvirus);
void init_virus(player_t *player,virus_t* virus,unsigned char nmaxvirus);

/*
    Every second call this function in order to determine how long
    to keep a virues alive
*/
void determine_is_virues_alive(virus_t* varr,unsigned char nvirueses);

#endif