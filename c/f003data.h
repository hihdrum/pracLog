#ifndef F003_DATA_H
#define F003_DATA_H

#include <stdint.h>

#pragma pack(push, 1)

typedef struct f003_data
{
  char type[3]; /* DXX */
  char data[0]; /* F003_DXX */
} F003_Header;

typedef struct f003_d001
{
  int16_t len; /* ペイロード長 */
  unsigned char payload[0];
} F003_D001;

#pragma pack(pop)

#endif
