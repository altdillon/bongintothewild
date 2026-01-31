#ifndef SCROLLING_H
#define SCROLLING_H
#include "player.h"
typedef struct 
{
    // x and y values for the location of the window
    unsigned char sx;
    unsigned char sy;
}scroll_t;

void map_scroll(scroll_t *scroll,player_t *player,char ncontroller);

#endif