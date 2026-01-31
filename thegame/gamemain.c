
// include NESLIB header
#include "./../neslib/neslib.h"
#include "pallets.h"
#include "gameconfig.h"
#include "player.h"

void setup_graphics();
void move_player(player_t *player);

// main function, run after console reset
void main(void)
{
  player_t player;
  player.px = 120;
  player.py = 120;
  player.dx = 1;
  player.dy = 3;
  player.ctrlr = 0;
  player.playerSp = 4;

  setup_graphics();
  while(1)
  {
    oam_clear();
    oam_spr(player.px, player.py, player.playerSp, 0,0);
    ppu_wait_nmi();

    // update player from the controller
    move_player(&player);
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

