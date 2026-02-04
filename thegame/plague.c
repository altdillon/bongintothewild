#include "plague.h"
#include "./../neslib/neslib.h"


unsigned char conway_grid[100]=
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0x55, 0xAA, 0, 0, 0, 0, 0, 0,
    0, 0, 0xAA, 0x55, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

void compute_generation(){
    unsigned char row;
    unsigned char col;
    unsigned char of = 1;
    unsigned char tl, t, tr, ml, mr, bl, b, br, m;
    unsigned char pos = 0;
    unsigned char nei;
    unsigned char *source, *target;



unsigned char future_grid[100]=
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};




    for(row = 0; row < GRIDHEIGHT; row++)
    {
        for(col = 0; col < GRIDWIDTH; col++)
        {
            if(col%8 == 7)
            {
                pos++;
            }

            if (row == 0)
            {
                tl = 0;
                t = 0;
                tr = 0;
            }
            else
            {
                if(of ==0)
                {
                    tl = (conway_grid[pos-1-GRIDWIDTH/8]>>(7))&1;
                    ml = (conway_grid[pos-1]>>(7))&1;
                    bl = (conway_grid[pos-1+GRIDWIDTH/8]>>(7))&1;
                }
                else
                {
                    tl = (conway_grid[pos-GRIDWIDTH/8]>>(of-1))&1;
                    ml = (conway_grid[pos]>>(of-1))&1;
                    bl = (conway_grid[pos+GRIDWIDTH/8]>>(of-1))&1;
                }
                
                t = (conway_grid[pos-GRIDWIDTH/8]>>(of))&1;
                m = (conway_grid[pos]>>(of))&1;
                b = (conway_grid[pos+GRIDWIDTH/8]>>(of))&1;
                

                if (of == 7)
                {
                    tr = (conway_grid[pos-GRIDWIDTH/8 + 1]&1);
                    mr = (conway_grid[pos + 1]&1);
                    br = (conway_grid[pos+GRIDWIDTH/8 + 1]&1);
                }
                else
                {
                    tr = (conway_grid[pos-GRIDWIDTH/8]>>(of+1))&1;
                    mr =(conway_grid[pos]>>(of+1))&1;
                    br = (conway_grid[pos+GRIDWIDTH/8]>>(of+1))&1;
                }
            }
            if(row==GRIDHEIGHT-1)
            {
                bl = 0;
                b = 0;
                br = 0;
            }

            nei = tl+t+tr+ml+mr+bl+b+br;
            if (m ==1 && nei == 2)
            {
               future_grid[pos] += 1<<of;
            }

            if(nei ==3)
            {
               future_grid[pos] += 1<<of;
            }



            of++;
            if (of==8)
            {
                of =0;
            }
        }
        
    }
    
    source = future_grid;
    target = conway_grid;
    pos = (GRIDWIDTH * GRIDHEIGHT)/8;


    while (0 < pos--)
    {
        *(target++) = *(source++);
    }
    
 
}

/*
    Draw the sprites for the plege
    spr_id is the last used sprite id
    generating is the array of cells
    ncells is number of cells
*/
unsigned char draw_virus(virus_t* virus, player_t* player, unsigned char spr_id)
{
   return oam_spr(virus->x+player->map_posx,virus->y+player->map_posy,PLAGUE_SPRITE_INDEX,VIRUS_PALETTE,spr_id);
}
unsigned char sqrt(unsigned int x)
{
    unsigned char sum = 0;
    if(x < 100)
    {
        sum += 7;
        sum += (x-49)/14;
        sum -= (x-49)*(x-49)/2744;
    }
    else
    {
        sum += 50;
        sum += (x-2500)/100;
        sum -= (x-2500)*(x-2500)/1000000;
    }
    if (sum < 1)
    {
        sum = 1;
    }
    return sum;
}

void move_virus(virus_t* virus, player_t* player,unsigned char nvirus)
{
    // char vx = player->px - virus->x - player->map_posx;
    // char vy = player->py - virus->y - player->map_posy;

    // unsigned int norm = vx*vx + vy*vy;
    // unsigned char s = sqrt(norm);
    // vx = vx * virus->dx/s;
    // vy = vy * virus->dy/s;
    // virus->x += vx;
    // virus->y += vy;

}

