#ifndef MASK_H
#define MASK_H
#include "gameconfig.h"

// struct for mask data
typedef struct 
{
    // define the x and y position on the screen
    unsigned char x;
    unsigned char y;
} mask_t;


// function prototypes
void compute_masks(mask_t *array,unsigned char nmasks);

#endif