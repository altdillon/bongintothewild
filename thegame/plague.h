#ifndef PLAGUE_H
#define PLAGUE_H
#define CELL_DEAD 0
#define CELL_ALIVE 1
#include "gameconfig.h"

/*
    Store information about the plague in question
*/

typedef struct 
{
    unsigned short px;
    unsigned short py;
    unsigned char sprite_index;
    unsigned char cell_state;
}virtus_t;


#endif