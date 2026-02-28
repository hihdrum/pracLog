#ifndef F001_DATA_H
#define F001_DATA_H

#include <stdint.h>

#pragma pack(push, 1)

typedef struct f001_data
{
  char type[3]; /* DXX */
  char data[0]; /* F001_DXX */
} F001_Header;

typedef struct f001_d001
{
  int16_t position;
} F001_D001;

typedef struct f001_d002
{
  int16_t x;
  int16_t y;
} F001_D002;

typedef struct f001_d003
{
  int16_t x;
  int16_t y;
  int16_t z;
} F001_D003;

#pragma pack(pop)

#endif
