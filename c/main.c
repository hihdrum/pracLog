#include <stdio.h>
#include <string.h>

#include "log.h"
#include "f001data.h"
#include "f002data.h"
#include "f003data.h"

int main(void)
{
  unsigned char buffer[256] = {0};

  /* F001_D001データのログ */
  LogRecord *pLogRecord = (LogRecord *)buffer;
  LogHeader *pLogHeader = &pLogRecord->header;
  F001_Header *pF001Header = (F001_Header *)pLogRecord->payload;
  F001_D001 *pF001D001 = (F001_D001 *)pF001Header->data;

  *pF001D001 = (F001_D001){ .position = 0x1122 };
  *pF001Header = (F001_Header){ .type = "D001" };

  char sizeBuffer[9];
  snprintf(sizeBuffer, sizeof(sizeBuffer), "%08ld",
    sizeof(*pF001Header) + sizeof(*pF001D001));

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
