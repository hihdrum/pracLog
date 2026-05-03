#include <stdlib.h>

#include "randInt.h"

int getRandomInt16(void)
{
  return (int16_t)(rand() & 0x7FFF);
}

/************************************************************
 * @brief 指定範囲内の乱数を得ます。
 *
 * @pram[in] 最小値
 * @pram[in] 最大値
 * @return min <= int <= max
 ************************************************************/
int random_range(int min, int max)
{
  return (rand() % (max - min + 1)) + min;
}

