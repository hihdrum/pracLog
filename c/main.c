#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "log.h"
#include "f001data.h"
#include "f002data.h"
#include "f003data.h"

/* F001 データ書込み用 */
int getRandomInt16(void)
{
  return (int16_t)(rand() & 0x7FFF);
}

F001_D001 rand_F001D001(void)
{
  return (F001_D001){ .position = getRandomInt16() };
}

unsigned char *write_F001_D001_data(unsigned char *buffer)
{
  F001_Header *pF001Header = (F001_Header *)buffer;
  F001_D001 *pF001D001 = (F001_D001 *)pF001Header->data;

  *pF001D001 = rand_F001D001();
  *pF001Header = (F001_Header){ .type = "D001" };

  return (unsigned char *)(pF001D001 + 1);
}

int main(void)
{
  srand(0);
  unsigned char buffer[256] = {0};

  /* F001_D001データのログ */
  LogRecord *pLogRecord = (LogRecord *)buffer;
  LogHeader *pLogHeader = &pLogRecord->header;
  F001_Header *pF001Header = (F001_Header *)pLogRecord->payload;
  unsigned char *pBufferTail = write_F001_D001_Data(pLogRecord->payload);

  char sizeBuffer[9];
  snprintf(sizeBuffer, sizeof(sizeBuffer), "%08ld",
    pBufferTail - (unsigned char *)pF001Header);

  pLogRecord->header = (LogHeader){
    .date = "20260102",
    .time = "112233444",
    .kind = "F001",
  };

  memcpy(&pLogRecord->header.size, sizeBuffer,
    sizeof(pLogRecord->header.size));

  fwrite(buffer, sizeof(buffer), 1, stdout);

  return 0;
}
