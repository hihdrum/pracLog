#ifndef F002_DATA_H
#define F002_DATA_H

#include <stdint.h>

#pragma pack(push, 1)

typedef struct f002_data
{
  char type[3]; /* DXX */
  char data[0]; /* F002_DXX */
} F002_Header;

typedef struct f002_d001
{
  int8_t len; /* メッセージ長 */
  char message[32];
} F002_D001;

#pragma pack(pop)

#endif
