
// include NESLIB header
#include "./../neslib/neslib.h"
#include "pallets.h"
#include "gameconfig.h"
#include "controller.h"

// struct to hold some basic information about the player
typedef struct {
  unsigned char px;
  unsigned char py;
} player_t;

void setup_graphics();

// main function, run after console reset
void main(void)
{
  player_t player;
  player.px = 120;
  player.py = 120;

  setup_graphics();
  while(1)
  {
    oam_clear();
    oam_spr(player.px, player.py, 0x04, 0,0);
    ppu_wait_nmi();
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

