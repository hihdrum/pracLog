#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "log.h"
#include "log_generator.h"
#include "f001data.h"
#include "f002data.h"
#include "f003data.h"
#include "log_time.h"

const LogPayloadWriter lpws[] = {
  { .kind = "F001", .writer = write_F001_D001_data },
  { .kind = "F001", .writer = write_F001_D002_data },
  { .kind = "F002", .writer = write_F002_D001_data },
  { .kind = "F003", .writer = write_F003_D01_data },
};

#define D_LOG_PAYLOAD_WRITERS (sizeof(lpws)/sizeof(lpws[0]))

int main(void)
{
  const int c_sample_data_num = 20;
  srand(0);

  const char *log_start_time_str = "2025/01/01 00:00:00.000";
  struct timespec log_time = parse_date_time(log_start_time_str);

  int i = 0;
  do
  {
    unsigned char buffer[256] = {0};

    /* F001_DXXデータのログ */
    LogRecord *pLogRecord = (LogRecord *)buffer;

    int typeD = rand() % D_LOG_PAYLOAD_WRITERS;
    const LogPayloadWriter *pLpw = &lpws[typeD];
    unsigned char *pBufferTail = write_LogRecord(log_time, pLpw, pLogRecord);

    fwrite(buffer, pBufferTail - buffer, 1, stdout);
    log_time = add_random_ms(&log_time, 10, 2000);

  } while(++i < c_sample_data_num);

  return 0;
}
