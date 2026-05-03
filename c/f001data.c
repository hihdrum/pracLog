#include "randInt.h"
#include "f001data.h"

/************************************************************
 * @brief ランダムなF001_D001データを返します。
 *
 * @return F001_D001
 ************************************************************/
F001_D001 rand_F001_D001(void)
{
  return (F001_D001){ .position = getRandomInt16() };
}

/************************************************************
 * @brief バッファにランダムなF001_D001データを書き込みます。
 *
 * @note バッファにはデータ書き込みに十分なサイズがある想定で動作します。
 * @pram[out] 書き込み先バッファアドレス
 * @return 書き込み後のバッファアドレス
 ************************************************************/
unsigned char *write_F001_D001_data(unsigned char *buffer)
{
  F001_Header *pF001Header = (F001_Header *)buffer;
  F001_D001 *pF001_D001 = (F001_D001 *)pF001Header->data;

  *pF001_D001 = rand_F001_D001();
  *pF001Header = (F001_Header){ .type = "D001" };

  return (unsigned char *)(pF001_D001 + 1);
}

/************************************************************
 * @brief ランダムなF001_D002データを返します。
 *
 * @return F001_D002
 ************************************************************/
F001_D002 rand_F001_D002(void)
{
  return (F001_D002){
      .x = getRandomInt16(),
      .y = getRandomInt16()
    };
}

/************************************************************
 * @brief バッファにランダムなF001_D002データを書き込みます。
 *
 * @note バッファにはデータ書き込みに十分なサイズがある想定で動作します。
 * @pram[out] 書き込み先バッファアドレス
 * @return 書き込み後のバッファアドレス
 ************************************************************/
unsigned char *write_F001_D002_data(unsigned char *buffer)
{
  F001_Header *pF001Header = (F001_Header *)buffer;
  F001_D002 *pF001_D002 = (F001_D002 *)pF001Header->data;

  *pF001_D002 = rand_F001_D002();
  *pF001Header = (F001_Header){ .type = "D002" };

  return (unsigned char *)(pF001_D002 + 1);
}
