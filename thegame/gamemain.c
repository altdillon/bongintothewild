
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
#include "maskitem.h"

//include nametables for all the screens such as title or game over

//#include "game_nam.h"


void put_str(unsigned int adr, const char *str);
void setup_graphics();
void move_player(player_t *player);
void play_state();
void title_screen();
void show_title_screen(const byte* pal, const byte* rle);
void display_static_background(const byte* pal, const byte* rle,const byte* attr_table ,unsigned int adr);
void you_died_screen();

// global values
unsigned short frame_count; // counter for keeping a running count of the frames
unsigned short seconds;

// global game state value
gamestatus_t gamestate;

// main function, run after console reset
void main(void)
{
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
      gamestate = YOUDIED;
      break;
  
    case TITLESCREEN:
      title_screen();
      gamestate = GAMETIME;
      break;

    case YOUDIED:
      you_died_screen(); 
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
  unsigned char i;
  char ran_random_virus=1;
  unsigned short day_count;
  unsigned char spr_id;
  unsigned char lucky_number;
  unsigned char num_masks; // how many masks to draw on the screen if we're going to do that
  unsigned char num_viruses; // number of viruses that will be drawn on the screen
  char strbuffer[32];
  char running;
  mask_t mask_array[MAX_MASKS];
  player_t player; // player object
  virus_t virus_arr[MAX_MASKS];
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
  // init the number of masks on the screen to zero
  num_masks = 0;
  num_viruses = 0;

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
    // check to see if the start button has been pressed
    // figure out if we have to scroll
    // scroll if we need to
    /*
      Draw logic 
    */
    map_scroll(&scroller,&player,0);
    scroll(scroller.sx,scroller.sy);

    // Test code for moving a virus on the screen
    if(num_viruses > 0)
    {
      //spr_id = 0;
      for(i=0;i<num_viruses;i++)
      {
        // draw the virus sprites, but with an offset
        spr_id = oam_spr(virus_arr[i].x-scroller.sx,virus_arr[i].y-scroller.sy,PLAGUE_SPRITE_INDEX,VIRUS_PALETTE,spr_id);
      }
    }

    // draw masks on the screen
    if(num_masks > 0)
    {
      for(i=0;i<num_masks;i++)
      {
        spr_id = oam_spr(mask_array[i].x-scroller.sx,mask_array[i].y-scroller.sy,MASK_SPRITE_INDEX,MASK_SPRITE_PALETTE,spr_id);
        mask_array[i].oam_id = spr_id; // save the oam id of the mask sprite after we draw it
      }
    }

    /*
      Game logic
    */

    frame_count++; // as this says, update the frame count

    /*
      loop through the virues and figure out if there's a hit or not
    */
    for(i=0;i<num_viruses;i++)
    {
      if(dist_from_player(&player,&virus_arr[i]) < VIRUS_MIN_DIST)
      {
        //running = 0; // for now just kill the player
        // if contact with a virues is recorded, subtract that from the player's heath
        player.health -= VIRUS_DAMAGE;
      }
    }

    /*
      Figure out if there's a mask with in some range of the player
      if we hit a mask then we add some value to the health
      if num_masks is zero, then this loop won't run 
    */    
    for(i=0;i<num_masks;i++)
    {
      if(mask_dist_from_player(&player,&mask_array[i]) < VIRUS_MIN_DIST)
      {
        player.health += MASK_HEALTH_VALUE;
        // now to delete the mask

      }
    }

    // determine if the player has enough health to keep playing
    if(player.health <= VIRUS_DAMAGE)
    {
      running = 0; // kill the game, this will go to the "you died" screen
    }   

    if(frame_count % 30 == 0)
    {
      // after everything is all said and done, move the virues
      move_virus(virus_arr, &player,num_viruses);
    }
    if(frame_count % 60 == 0) // counter for events that happen once a second
    {
      num_viruses = determine_is_virues_alive(virus_arr,num_viruses);
      seconds++;
      if(seconds % DAY_LENGTH == 0) // is daycount a multiple of 90?
      {
        day_count++;
      }
    }
    // check if t he player is lucky every 6 seconds
    if(seconds % 6 ==0 && num_masks == 0)
    {
      // take a random number to compute how many maks to draw.
      // do like double luck lol
      num_masks = rndint(1,MAX_MASKS);
      compute_masks(mask_array,num_masks);
    }

    // check if the player is unluky every 3 seconds
    if(seconds % 3 == 0 && !ran_random_virus && num_viruses < 1)
    {
      ran_random_virus = 1;
   
      lucky_number = rndint(1,10);
      if(lucky_number >= 6)
      {
        // player is un lucky and must face punishment for a randum nucker picked by a 40 year old gaming console 
        // punish them!

        num_viruses = rndint(2,MAX_VIRUS);
        init_virus(&player,virus_arr,num_viruses);
      }
    }   

    if(num_viruses == 0)
    {
      ran_random_virus = 0;
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

void you_died_screen()
{
  // old you died screen...
  // put_str(NAMETABLE_A,"you died");
  // while(1);

  ppu_off();

  // clear the name table and attributes
  vram_adr(NAMETABLE_A);
  vram_fill(0x00,960);
  vram_fill(0x00,64);

  display_static_background(youdied_palette,youdied,youdied_attr,NAMETABLE_A);

  ppu_on_all();
  oam_clear(); // get rid of any spries on the screen
  // zero out scrolling
  scroll(0,0);
  ppu_wait_nmi();
  while(1); // just wait for the system to be reset

}