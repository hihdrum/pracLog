#include <string.h>

#include "randInt.h"
#include "f003data.h"

/************************************************************
 * @brief バッファにランダムなF003_D01データを書き込みます。
 *
 * @note バッファにはデータ書き込みに十分なサイズがある想定で動作します。
 * @pram[out] 書き込み先バッファアドレス
 * @return 書き込み後のバッファアドレス
 ************************************************************/
unsigned char *write_F003_D01_data(unsigned char *buffer)
{
  F003_Header *pF003Header = (F003_Header *)buffer;
  F003_D01 *pF003_D01 = (F003_D01 *)pF003Header->data;

  int16_t len = random_range(0, 16);
  char message_char = random_range('a', 'z');

  pF003_D01->len = len;
  memset(pF003_D01->payload, message_char, len);

  *pF003Header = (F003_Header){ .type = "D01" };

  return (unsigned char *)(pF003_D01->payload + len);
}
