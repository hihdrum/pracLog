#ifndef F003_DATA_H
#define F003_DATA_H

#include <stdint.h>

#pragma pack(push, 1)

typedef struct f003_data
{
  char type[3]; /* DXX */
  char data[0]; /* F003_DXX */
} F003_Header;

typedef struct f003_d01
{
  int16_t len; /* ペイロード長 */
  unsigned char payload[0];
} F003_D01;

#pragma pack(pop)

unsigned char *write_F003_D01_data(unsigned char *buffer);

#endif
