
// include NESLIB header
#include <stdio.h>
#include <string.h>
#include "./../neslib/neslib.h"
#include "pallets.h"
#include "gameconfig.h"
#include "player.h"
#include "scrolling.h"
#include "vrambuf.h"
#include "assets.h"
#include "gamestate.h"


//include nametables for all the screens such as title or game over

//#include "game_nam.h"


// function to write a string into the name table
//   adr = start address in name table
//   str = pointer to string
void put_str(unsigned int adr, const char *str);
void setup_graphics();
void move_player(player_t *player);
void play_state();
void title_screen();
void show_title_screen(const byte* pal, const byte* rle);
void display_static_background(const byte* pal, const byte* rle,const byte* attr_table ,unsigned int adr);

// global values
unsigned short frame_count; // counter for keeping a running count of the frames
unsigned short seconds;

// main function, run after console reset
void main(void)
{
  gamestatus_t gamestate;
  // informal values for game state
  // NOTE: This may get turned into a struct in the future 
  frame_count = 0;
  seconds = 0;

  gamestate = TITLESCREEN;
  // 

  while(1)
  {
    switch (gamestate)
    {
    case GAMETIME:
      
      play_state();
      break;
  
    case TITLESCREEN:
      title_screen();
      gamestate = GAMETIME;
      break;

    default:
      break;
    }
 
  }
}

void show_title_screen(const byte* pal, const byte* rle)
{
  ppu_off();

  pal_bg(pal);
  pal_bright(4);
  vram_adr(0x2000);
  vram_unrle(rle);
  vram_write(title_attribute_table,sizeof(title_attribute_table)); // this maybe shouldn't be hard coded, but who cares.
  ppu_on_all();
}

void display_static_background(const byte* pal, const byte* rle,const byte* attr_table ,unsigned int adr)
{
  pal_bg(pal);
  vram_adr(adr);
  vram_unrle(rle);
  vram_write(attr_table,64);
}

void title_screen()
{
    char i, start_btn = 0, pad;

    show_title_screen(title_palette, hello_rle);

    // wait for start button
    while(start_btn != 1) {
        for(i = 0; i < 2; i++) {
            pad = pad_poll(i);
            if(pad & PAD_START) start_btn = 1;
        }
        ppu_wait_nmi(); // wait for next frame
    }

    // clear screen before moving on
    ppu_off();
    vram_adr(NAMETABLE_A);
    vram_fill(0x00, 960);
    vram_fill(0x00, 64);
    ppu_on_all();
    ppu_off();
}


/*
  function for the game play state
*/
void play_state()
{
  char strbuffer[32];
  char running;
  player_t player; // player object
  scroll_t scroller;
  //Window_t window; // location of the window

  memset(strbuffer,'\0',32);
  running = 1;
  // init the player
  player.px = 120;
  player.py = 120;
  player.dx = 3;
  player.dy = 3;
  player.ctrlr = 0;
  player.playerSp = 0xB1;

  // game play veriables
  player.health = DEFAULT_HEALTH; 
  player.immunity = DEFAULT_IMMUNITY;
  player.dir = PLAYER_NORTH;

  // init the scroller
  scroller.sx = 0;
  scroller.sy = 0;

  // write text to name table
  // put_str(NTADR_A(2,0), "Nametable A, Line 0");
  // put_str(NTADR_A(2,15), "Nametable A, Line 15");
  // put_str(NTADR_A(2,29),"Nametable A, Line 29");
  // put_str(NTADR_C(2,0), "Nametable C, Line 0");
  // put_str(NTADR_C(2,15), "Nametable C, Line 15");
  // put_str(NTADR_C(2,29),"Nametable C, Line 29");

  // write the static background image to Nametables A and C
  display_static_background(background_palette, nesstBackground,backGroundAttertable, NAMETABLE_A);
  display_static_background(background_palette, nesstBackground,backGroundAttertable, NAMETABLE_C);

  pal_spr(spr_palette);
    
  setup_graphics();
  while(running)
  {
    oam_clear(); // clear off all the old sprites
    updbuf[0] = NT_UPD_EOF;
    // draw the player, and then use the vram buffer to draw any other enviroment related stuff onto the screen 
    oam_spr(player.px, player.py, player.playerSp, 0,0);
    // test stuff...  
    // test table A
    // sprintf(strbuffer,"Nametable A, Line 0 %d",seconds);
    // vrambuf_put(NTADR_A(2,0),strbuffer,strlen(strbuffer));
    // sprintf(strbuffer,"Nametable A, Line 15");
    // vrambuf_put(NTADR_A(2,15),strbuffer,strlen(strbuffer));
    // sprintf(strbuffer,"Nametable A, Line 29");
    // vrambuf_put(NTADR_A(2,26),strbuffer,strlen(strbuffer));
    // test table C
    // sprintf(strbuffer,"Nametable C, Line 0");
    // vrambuf_put(NTADR_C(2,0),strbuffer,strlen(strbuffer));
    // sprintf(strbuffer,"Nametable C, Line 15");
    // vrambuf_put(NTADR_C(2,15),strbuffer,strlen(strbuffer));
    // sprintf(strbuffer,"Nametable C, Line 29");
    // vrambuf_put(NTADR_C(2,26),strbuffer,strlen(strbuffer));
    //ppu_wait_nmi();
    // end of test stuff... 
    // update player from the controller
    move_player(&player);
    // figure out if we have to scroll
    // scroll if we need to
    //map_scroll(scroll_t *scroll, player_t *player, char ncontroller)
    map_scroll(&scroller,&player,0);
    scroll(scroller.sx,scroller.sy);

    frame_count++;
    if(frame_count % 60 == 0)
    {
      seconds++;
    }
    ppu_wait_nmi();
  }
}

void setup_graphics()
{
  // clear the sprites and turn on the ppu
  oam_clear();
  // set palette colors
  //pal_all(PALETTE);
  // clear the VRAM buffer
  vrambuf_clear();
  // set the NMI handler
  set_vram_update(updbuf);
  // turn on PPU
  ppu_on_all();
}

void put_str(unsigned int adr, const char *str) 
{
  vram_adr(adr);        // set PPU read/write address
  vram_write(str, strlen(str)); // write bytes to PPU
}