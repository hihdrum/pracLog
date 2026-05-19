#include "randInt.h"
#include "f001data.h"

/************************************************************
 * @brief ランダムなF001_D001データを返します。
 *
 * @return F001_D001
 ************************************************************/
F001_D001 rand_F001_D001(void)
{
  return (F001_D001){ .position = get_random_int16() };
}

/************************************************************
 * @brief バッファにランダムなF001_D001データを書き込みます。
 *
 * @note バッファにはデータ書き込みに十分なサイズがある想定で動作します。
 * @pram[out] 書き込み先バッファアドレス
 * @return 書き込み後のバッファアドレス
 ************************************************************/
unsigned char *write_F001_D001_data(const void *arg, unsigned char *buffer)
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
      .x = get_random_int16(),
      .y = get_random_int16()
    };
}

/************************************************************
 * @brief バッファにランダムなF001_D002データを書き込みます。
 *
 * @note バッファにはデータ書き込みに十分なサイズがある想定で動作します。
 * @pram[out] 書き込み先バッファアドレス
 * @return 書き込み後のバッファアドレス
 ************************************************************/
unsigned char *write_F001_D002_data(const void *arg, unsigned char *buffer)
{
  F001_Header *pF001Header = (F001_Header *)buffer;
  F001_D002 *pF001_D002 = (F001_D002 *)pF001Header->data;

  *pF001_D002 = rand_F001_D002();
  *pF001Header = (F001_Header){ .type = "D002" };

  return (unsigned char *)(pF001_D002 + 1);
}

/************************************************************
 * @brief バッファにランダムなF001_D002データを書き込みます。
 *
 * @note バッファにはデータ書き込みに十分なサイズがある想定で動作します。
 * @param[in] arg : F002_ScaleFactorとする。
 * @param[out] 書き込み先バッファアドレス
 * @return 書き込み後のバッファアドレス
 ************************************************************/
unsigned char *write_F001_D002_data_sf(const void *arg, unsigned char *buffer)
{
  const F001_D002_ScaleFactor *pSF = (F001_D002_ScaleFactor *)arg;
  F001_Header *pF001Header = (F001_Header *)buffer;
  F001_D002 *pF001_D002 = (F001_D002 *)pF001Header->data;

  F001_D002 f001D002 = rand_F001_D002();
  f001D002 = (F001_D002){ pSF->xsf * f001D002.x, pSF->ysf * f001D002.y };

  *pF001_D002 = f001D002;
  *pF001Header = (F001_Header){ .type = "D002" };

  return (unsigned char *)(pF001_D002 + 1);
}
