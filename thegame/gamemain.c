
// include NESLIB header
#include "./../neslib/neslib.h"
#include "pallets.h"

void setup_graphics();

// main function, run after console reset
void main(void)
{
  setup_graphics();

  // infinite loop
  while (1);
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
