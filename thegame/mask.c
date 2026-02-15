#include "maskitem.h"
#include "rndhelper.h"
#include "player.h"

void compute_masks(mask_t *array,unsigned char nmasks)
{
    unsigned char i;
    for(i=0;i<nmasks;i++)
    {
        // compute the random x and y values
        array[i].x = rndint(1,127);
        array[i].y = rndint(1,127);
    }
}

void draw_mask_sprites(mask_t *maskarray,unsigned char nmasks,unsigned char spr_id)
{

}

unsigned char mask_dist_from_player(const player_t *player,const mask_t *masks,unsigned char nmasks)
{

    return 0;
}