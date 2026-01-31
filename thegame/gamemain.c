
// include NESLIB header
#include "./../neslib/neslib.h"
#include "pallets.h"
#include "gameconfig.h"
#include "controller.h"

// struct to hold some basic information about the player
typedef struct {
  int ctrlr; // controller that the player is driven by
  // position vector for the player
  unsigned char px;
  unsigned char py;
  // delta vector for the player
  unsigned char dx;
  unsigned char dy;
} player_t;

void setup_graphics();
void move_player(player_t *player);

// main function, run after console reset
void main(void)
{
  player_t player;
  player.px = 120;
  player.py = 120;
  player.dx = 3;
  player.dy = 3;
  player.ctrlr = 0;

  setup_graphics();
  while(1)
  {
    oam_clear();
    oam_spr(player.px, player.py, 0x04, 0,0);
    ppu_wait_nmi();

    // update player from the controller
    move_player(&player);
  }
}

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

void setup_graphics()
{
  // clear the sprites and turn on the ppu
  oam_clear();
  // set palette colors
  pal_all(PALETTE);
  // turn on PPU
  ppu_on_all();
}

