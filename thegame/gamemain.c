
// include NESLIB header
#include <stdio.h>
#include <string.h>
//#include <stdlib.h>
#include "./../neslib/neslib.h"
#include "pallets.h"
#include "gameconfig.h"
#include "player.h"
#include "scrolling.h"
#include "vrambuf.h"
#include "assets.h"
#include "gamestate.h"
#include "plague.h"
#include "rndhelper.h"

//include nametables for all the screens such as title or game over

//#include "game_nam.h"


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

// pre computed values for where viruses go
unsigned char circle_x[12]={20,16,10,0,-10,-16,-20,-16,-10,0,10,16};
unsigned char circle_y[12]={0,10,16,20,16,10,0,-10,-16,-20,-16,-10};




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
  char ran_random_virus=1;
  char virus_alive = 0;
  unsigned short day_count;
  unsigned char spr_id;
  unsigned char lucky_number;
  unsigned char num_masks; // how many masks to draw on the screen if we're going to do that
  char strbuffer[32];
  char running;
  player_t player; // player object
  char virus_x, virus_y;
  scroll_t scroller;
  //Window_t window; // location of the window
  day_count = 1; // start at one b/c this is day 1

  memset(strbuffer,'\0',32);
  running = 1;
  // init the player
  player.px = 120;
  player.py = 120;
  player.dx = 3;
  player.dy = 3;
  player.ctrlr = 0;
  player.playerSp = 0xB1;
  // init the player position in the map
  player.map_posx = 200;
  player.map_posy = 200;

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
    spr_id = oam_spr(player.px, player.py, player.playerSp, PLAYER_PALETTE,0);
  

      
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
      if(seconds % DAY_LENGTH == 0) // is daycount a multiple of 90?
      {
        day_count++;
      }
    }
    // check if t he player is lucky every 6 seconds
    if(seconds % 6 ==0)
    {
      // take a random number to compute how many maks to draw.
      // do like double luck lol
      num_masks = rndint(0,MAX_MASKS);
    }

    // check if the player is unluky every 3 seconds
    if(seconds % 3 == 0 && !ran_random_virus)
    {
      ran_random_virus = 1;
       if (virus_alive ==1)
        {
          virus_alive = rndint(0,1);
        }

      lucky_number = rndint(1,10);
      if(lucky_number > 6 && virus_alive == 0)
      {
        // player is un lucky and must face punishment for a randum nucker picked by a 40 year old gaming console 
        // punish them!

        lucky_number = rndint(0,12);
        virus_alive = 1;
        virus_x = player.px-player.map_posx+circle_x[lucky_number];
        virus_y = player.py-player.map_posy+circle_y[lucky_number];
      }
    }   

    if(seconds%3 ==1)
    {
      ran_random_virus =0;
    }
    if(virus_alive == 1)
    {

      spr_id = oam_spr(virus_x+player.map_posx,virus_y+player.map_posy,PLAGUE_SPRITE_INDEX,VIRUS_PALETTE,spr_id);
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
