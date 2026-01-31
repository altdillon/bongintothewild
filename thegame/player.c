#include "player.h"
#include "gameconfig.h"
#include "./../neslib/neslib.h"

void move_player(player_t *player)
{
  unsigned char pad;
  pad = pad_poll(player->ctrlr); // pad poll pulls down which buttons have actually been pressed
  
  if(pad & PAD_UP && (player->py + player->dy) > LOWER_SCROLL_LIMIT_Y)
  {
    player->py -= player->dy;
  }
  else if(pad & PAD_DOWN && (player->py - player->dy) <= UPPER_SCROLL_LIMIT_Y)
  {
    player->py += player->dy;
  }
  else if(pad & PAD_RIGHT && (player->px + player->dx) < UPPER_SCROLL_LIMIT_X)
  {
    player->px += player->dx;
  }
  else if(pad & PAD_LEFT && (player->px - player->dx) > LOWER_SCROLL_LIMIT_X)
  {
    player->px -= player->dx;
  }
}