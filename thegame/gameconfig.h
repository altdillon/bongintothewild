#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#define NACTORS 1 // number of actors that we're drawing on the screen
// X and Y denote the box that can be used to interact around the player
// limits for Y axis
#define LOWER_SCROLL_LIMIT_Y 20
#define UPPER_SCROLL_LIMIT_Y 200
// limits for the X axis
#define LOWER_SCROLL_LIMIT_X 20
#define UPPER_SCROLL_LIMIT_X 230
// sprite palette that the player is using
#define PLAYER_PALETTE 0
#define VIRUS_PALETTE 1
#define PLAGUE_SPRITE_INDEX 0xB9
#define VIRUS_MIN_DIST 20 // minium distance that's needed to register contact from a virues
// running numbers of viruses
#define MAX_VIRUS 10
#define VIRUS_MIN_DX 1
#define VIRUS_MAX_DX 4
#define VIRUS_MIN_DY 1
#define VIRUS_MAX_DY 4
#define VIRUS_DETECT_RAD 8
#define VIRUS_DAMAGE 3 // how many points of damage contact with a virues does
// min and max time that we can have the virues randomly stay alive for
#define VIRUS_MIN_TIME 2
#define VIRUS_MAX_TIME 10
// sprite information for the mask
#define MAX_MASKS 6    // max number of masks that can be shown on the scren, for some reason if this is less than 5 the game breaks.  I don't care enough to fix that...
#define MASK_SPRITE_INDEX 0xAF
#define MASK_SPRITE_PALETTE 0 
#define MASK_HEALTH_VALUE 3 // how many points of health each mask is worth

// game related values
#define DEFAULT_HEALTH 10
#define DEFAULT_IMMUNITY 20

// define the map bounderies.  
// These are the absoulte bounderies of the world map
#define WORLD_WIDTH 100
#define WORLD_HEIGHT 100

// variables for the pleage 
#define CELLNACTORS 20

// define how many seconds a Day is
#define DAY_LENGTH 90

#endif