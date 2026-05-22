#ifndef F002_DATA_H
#define F002_DATA_H

/************************************************************
 * @file f002data.h
 * @brief F002系データ
 * @note
 *  - F002系のデータはコンテナとして固定長であるが、
 *    内部のデータは可変長である。(最大が固定)
 ************************************************************/
#include <stdint.h>

#define D_F002_D001_MAX_MSG_LEN 32 /**< 0から255で設定すること。 */

#pragma pack(push, 1)

typedef struct f002_data
{
  char type[4]; /**< DXXX */
  char data[0]; /**< F002_DXXX */
} F002_Header;

typedef struct f002_d001
{
  int8_t len; /**< メッセージ長 */
  /**
   *  @brief メッセージバッファ
   *  @details
   *   - lenフィールドで有効長を指定する。
   *   - 有効長以外の部分は最大長までスペース埋めとする。
   */
  char message[D_F002_D001_MAX_MSG_LEN];
} F002_D001;

#pragma pack(pop)

unsigned char *write_F002_D001_data(const void *arg, unsigned char *buffer);

#endif
