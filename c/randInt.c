#include <stdlib.h>

#include "randInt.h"

int getRandomInt16(void)
{
  return (int16_t)(rand() & 0x7FFF);
}

