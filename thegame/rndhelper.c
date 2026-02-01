#include <stdlib.h>
#include "rndhelper.h"

// helper for 32 bit srand numbers
unsigned char rndint(unsigned char a,unsigned char b)
{
  return (rand() % (b-a)) + a;
}