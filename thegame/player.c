#include "player.h"
#include "./../neslib/neslib.h"

void move_player(player_t *player)
{
  unsigned char pad;
  pad = pad_poll(player->ctrlr);
  // figure out what buttons where pressed
  if(pad & PAD_UP)
  {
    player->py -= player->dy;
  }
  else if(pad & PAD_DOWN)
  {
    player->py += player->dy;
  }
  else if(pad & PAD_RIGHT)
  {
    player->px += player->dx;
  }
  else if(pad & PAD_LEFT)
  {
    player->px -= player->dy;
  }
}