
// include NESLIB header
#include <string.h>
#include "./../neslib/neslib.h"
#include "pallets.h"
#include "gameconfig.h"
#include "player.h"
#include "scrolling.h"

// function to write a string into the name table
//   adr = start address in name table
//   str = pointer to string
void put_str(unsigned int adr, const char *str);

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
  player.playerSp = 0xB1;

  // write text to name table
  put_str(NTADR_A(2,0), "Nametable A, Line 0");
  put_str(NTADR_A(2,15), "Nametable A, Line 15");
  put_str(NTADR_A(2,29),"Nametable A, Line 29");
  put_str(NTADR_C(2,0), "Nametable C, Line 0");
  put_str(NTADR_C(2,15), "Nametable C, Line 15");
  put_str(NTADR_C(2,29),"Nametable C, Line 29");

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

void put_str(unsigned int adr, const char *str) 
{
  vram_adr(adr);        // set PPU read/write address
  vram_write(str, strlen(str)); // write bytes to PPU
}