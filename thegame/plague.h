#ifndef PLAGUE_H
#define PLAGUE_H
#define CELL_DEAD 0
#define CELL_ALIVE 1
#include "gameconfig.h"
#define GRIDWIDTH 40
#define GRIDHEIGHT 20
#define PLAGUE_SPRITE_INDEX 0xB9

/*
    Store information about the plague in question
*/
extern unsigned char conway_grid[100];

void compute_generation();



#endif