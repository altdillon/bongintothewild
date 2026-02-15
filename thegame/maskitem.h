#ifndef MASK_H
#define MASK_H
#include "gameconfig.h"
#include "player.h"

// struct for mask data
typedef struct 
{
    // define the x and y position on the screen
    unsigned char x;
    unsigned char y;
} mask_t;


// function prototypes
void compute_masks(mask_t *array,unsigned char nmasks);
void draw_mask_sprites(mask_t *maskarray,unsigned char nmasks,unsigned char spr_id);
unsigned char mask_dist_from_player(const player_t *player,const mask_t *masks);

#endif