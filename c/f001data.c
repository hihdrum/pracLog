#include "randInt.h"
#include "f001data.h"

F001_D001 rand_F001_D001(void)
{
  return (F001_D001){ .position = getRandomInt16() };
}

/**
 * @return 次ペイロード開始アドレス
 */
unsigned char *write_F001_D001_data(unsigned char *buffer)
{
  F001_Header *pF001Header = (F001_Header *)buffer;
  F001_D001 *pF001_D001 = (F001_D001 *)pF001Header->data;

  *pF001_D001 = rand_F001_D001();
  *pF001Header = (F001_Header){ .type = "D001" };

  return (unsigned char *)(pF001_D001 + 1);
}

F001_D002 rand_F001_D002(void)
{
  return (F001_D002){ .x = getRandomInt16(),
                      .y = getRandomInt16()
                    };
}

unsigned char *write_F001_D002_data(unsigned char *buffer)
{
  F001_Header *pF001Header = (F001_Header *)buffer;
  F001_D002 *pF001_D002 = (F001_D002 *)pF001Header->data;

  *pF001_D002 = rand_F001_D002();
  *pF001Header = (F001_Header){ .type = "D002" };

  return (unsigned char *)(pF001_D002 + 1);
}

