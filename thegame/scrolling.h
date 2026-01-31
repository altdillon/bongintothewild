#ifndef SCROLLING_H
#define SCROLLING_H
typedef struct 
{
    // x and y values for the location of the window
    unsigned char windowX;
    unsigned char windowY;
}Window_t;

void map_scroll(unsigned char mx, unsigned char my);

#endif