#ifndef F001_DATA_H
#define F001_DATA_H

/* F001系のデータは固定長データをイメージしている。*/

#include <stdint.h>

#pragma pack(push, 1)

typedef struct f001_data
{
  char type[4]; /* DXXX */
  unsigned char data[0]; /* F001_DXXX */
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

F001_D001 rand_F001_D001(void);
unsigned char *write_F001_D001_data(unsigned char *buffer);

F001_D002 rand_F001_D002(void);
unsigned char *write_F001_D002_data(unsigned char *buffer);

#endif
