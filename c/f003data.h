#ifndef F003_DATA_H
#define F003_DATA_H

/************************************************************
 * @file f003data.h
 * @brief F003系データ
 * @note
 *  - F003系のデータはコンテナとして可変長である。
 ************************************************************/
#include <stdint.h>

#define D_F003_D01_MAX_MSG_LEN 16 /**< 0から書き込み先バッファに入るサイズで設定すること。 */

#pragma pack(push, 1)

typedef struct f003_data
{
  char type[3]; /**< DXX */
  char data[0]; /**< F003_DXX */
} F003_Header;

typedef struct f003_d01
{
  int16_t len; /* ペイロード長 */
  /**
   * @brief 可変長バッファ
   * @details
   *  - lenフィールドの長さ分のデータが続く。
   */
  unsigned char payload[0];
} F003_D01;

#pragma pack(pop)

unsigned char *write_F003_D01_data(unsigned char *buffer);

#endif
