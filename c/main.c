#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "log.h"
#include "f001data.h"
#include "f002data.h"
#include "f003data.h"
#include "log_time.h"

/* F001 データ書込み用 */
int getRandomInt16(void)
{
  return (int16_t)(rand() & 0x7FFF);
}

F001_D001 rand_F001D001(void)
{
  return (F001_D001){ .position = getRandomInt16() };
}

/**
 * @return ペイロード開始アドレス
 */
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

  const char *log_start_time_str = "2025/01/01 00:00:00.000";
  struct timespec log_time = parse_date_time(log_start_time_str);

  unsigned char buffer[256] = {0};

  /* F001_D001データのログ */
  LogRecord *pLogRecord = (LogRecord *)buffer;
  LogHeader *pLogHeader = &pLogRecord->header;
  F001_Header *pF001Header = (F001_Header *)pLogRecord->payload;
  unsigned char *pBufferTail = write_F001_D001_data(pLogRecord->payload);

  char sizeBuffer[9];

  /* 1回目 */
  snprintf(sizeBuffer, sizeof(sizeBuffer), "%08ld",
    pBufferTail - (unsigned char *)pF001Header);

  strcpy((char *)pLogHeader, log_date_time(&log_time));
  memcpy(pLogHeader->kind, "F001", sizeof(pLogHeader->kind));

  memcpy(&pLogRecord->header.size, sizeBuffer,
    sizeof(pLogRecord->header.size));

  fwrite(buffer, pBufferTail - buffer, 1, stdout);

  /* 2回目 */
  log_time = add_random_ms(&log_time, 10, 2000);

  pBufferTail = write_F001_D001_data(pLogRecord->payload);

  snprintf(sizeBuffer, sizeof(sizeBuffer), "%08ld",
    pBufferTail - (unsigned char *)pF001Header);

  strcpy((char *)pLogHeader, log_date_time(&log_time));
  memcpy(pLogHeader->kind, "F001", sizeof(pLogHeader->kind));

  memcpy(&pLogRecord->header.size, sizeBuffer,
    sizeof(pLogRecord->header.size));

  fwrite(buffer, pBufferTail - buffer, 1, stdout);

  return 0;
}
