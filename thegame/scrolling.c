#include "scrolling.h"
#include "gameconfig.h"
#include "./../neslib/neslib.h"


// void map_scroll(unsigned char mx, unsigned char my)
// {
    
// }

void map_scroll(scroll_t *scroll,player_t *player,char ncontroller)
{
    unsigned char pad;
    pad = pad_poll(ncontroller);

    // determine if the player is moving

  if(pad & PAD_UP && (player->py + player->dy) > LOWER_SCROLL_LIMIT_Y)
  {
    scroll->sy -= 1;
  }
  if(pad & PAD_DOWN && (player->py - player->dy) <= UPPER_SCROLL_LIMIT_Y)
  {
    scroll->sy += 1;
  }
  if(pad & PAD_RIGHT && (player->px + player->dx) > UPPER_SCROLL_LIMIT_X)
  {
    scroll->sx += 1;
  }
  if(pad & PAD_LEFT && (player->px - player->dx) < LOWER_SCROLL_LIMIT_X)
  {
    scroll->sx -= 1;
  }
}