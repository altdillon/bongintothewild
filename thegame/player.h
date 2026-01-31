#ifndef PLAYER_H
#define PLAYER_H

// struct to hold some basic information about the player
typedef struct {
  int ctrlr; // controller that the player is driven by
  // position vector for the player
  unsigned char px;
  unsigned char py;
  // delta vector for the player
  unsigned char dx;
  unsigned char dy;
  // player sprite
  unsigned char playerSp;
} player_t;


void move_player(player_t *player);

#endif