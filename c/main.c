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

F001_D001 rand_F001_D001(void)
{
  return (F001_D001){ .position = getRandomInt16() };
}

F001_D002 rand_F001_D002(void)
{
  return (F001_D002){ .x = getRandomInt16(),
                      .y = getRandomInt16()
                    };
}

/**
 * @return 次ペイロード開始アドレス
 */
unsigned char *write_F001_D001_data(unsigned char *buffer)
{
  F001_Header *pF001Header = (F001_Header *)buffer;
  F001_D001 *pF001_D001 = (F001_D001 *)pF001Header->data;

  *pF001_D001 = rand_F001_D001();
  *pF001Header = (F001_Header){ .type = "D001" };

  return (unsigned char *)(pF001_D001 + 1);
}

unsigned char *write_F001_D002_data(unsigned char *buffer)
{
  F001_Header *pF001Header = (F001_Header *)buffer;
  F001_D002 *pF001_D002 = (F001_D002 *)pF001Header->data;

  *pF001_D002 = rand_F001_D002();
  *pF001Header = (F001_Header){ .type = "D002" };

  return (unsigned char *)(pF001_D002 + 1);
}

typedef struct logPayloadWriter
{
  char kind[4];
  unsigned char* (*writer)(unsigned char *);
} LogPayloadWriter;

const LogPayloadWriter lpwF001D001 = { .kind = "F001", .writer = write_F001_D001_data };
const LogPayloadWriter lpwF001D002 = { .kind = "F001", .writer = write_F001_D002_data };

unsigned char *write_LogRecord(struct timespec log_time, const LogPayloadWriter *lpw, LogRecord *buffer)
{
    LogRecord *pLogRecord = (LogRecord *)buffer;
    LogHeader *pLogHeader = &pLogRecord->header;

    unsigned char *pKindHeader = pLogRecord->payload;
    unsigned char *pBufferTail = lpw->writer(pKindHeader);

    char sizeBuffer[9];
    snprintf(sizeBuffer, sizeof(sizeBuffer), "%08ld", pBufferTail - pKindHeader);

    strcpy((char *)pLogHeader, log_date_time(&log_time));
    memcpy(pLogHeader->kind, lpw->kind, sizeof(pLogHeader->kind));

    memcpy(&pLogRecord->header.size, sizeBuffer,
      sizeof(pLogRecord->header.size));

  return pBufferTail;
}

int main(void)
{
  srand(0);

  const char *log_start_time_str = "2025/01/01 00:00:00.000";
  struct timespec log_time = parse_date_time(log_start_time_str);

  int i = 0;
  do
  {
    unsigned char buffer[256] = {0};

    /* F001_DXXデータのログ */
    LogRecord *pLogRecord = (LogRecord *)buffer;

    /* 偶数:D001, 奇数:D002 とする。*/
    int typeD = rand() % 2;
    if(0 == typeD)
    {
      /* F001_D001 */
      unsigned char *pBufferTail = write_LogRecord(log_time, &lpwF001D001, pLogRecord);

      fwrite(buffer, pBufferTail - buffer, 1, stdout);
      log_time = add_random_ms(&log_time, 10, 2000);
    }
    else
    {
      /* F001_D002 */
      unsigned char *pBufferTail = write_LogRecord(log_time, &lpwF001D002, pLogRecord);

      fwrite(buffer, pBufferTail - buffer, 1, stdout);
      log_time = add_random_ms(&log_time, 10, 2000);
    }
  } while(++i < 10);

  return 0;
}
