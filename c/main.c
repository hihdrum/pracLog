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

const LogPayloadWriter lpws[] = {
  { .kind = "F001", .writer = write_F001_D001_data },
  { .kind = "F001", .writer = write_F001_D002_data },
};

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

    int typeD = rand() % 2;
    const LogPayloadWriter *pLpw = &lpws[typeD];
    unsigned char *pBufferTail = write_LogRecord(log_time, pLpw, pLogRecord);

    fwrite(buffer, pBufferTail - buffer, 1, stdout);
    log_time = add_random_ms(&log_time, 10, 2000);

  } while(++i < 10);

  return 0;
}
