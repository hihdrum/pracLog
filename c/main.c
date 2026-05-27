#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "log.h"
#include "log_generator.h"
#include "log_generator_with_weight.h"
#include "f001data.h"
#include "f002data.h"
#include "f003data.h"
#include "log_time.h"

const LogPayloadWriterWithWeight lpws_ww[] = {
  { .writer = { .kind = "F001", .writer = write_F001_D001_data, .arg = NULL }, .weight = 30 },
  { .writer = { .kind = "F001", .writer = write_F001_D002_data, .arg = NULL }, .weight = 25 },
  { .writer = { .kind = "F001", .writer = write_F001_D002_data_sf, .arg = &(F001_D002_ScaleFactor){ .xsf = 10, .ysf = 0 }}, .weight = 25 },
  { .writer = { .kind = "F002", .writer = write_F002_D001_data, .arg = NULL }, .weight = 10 },
  { .writer = { .kind = "F003", .writer = write_F003_D01_data, .arg = NULL }, .weight = 10 },
};

#define D_LOG_PAYLOAD_WRITERS_WITH_WEIGHT (sizeof(lpws_ww)/sizeof(lpws_ww[0]))

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
    LogRecord *pLogRecord = (LogRecord *)buffer;

    const LogPayloadWriter *pLpw = LGWW_getRandomLogPayloadWriter(lpws_ww, D_LOG_PAYLOAD_WRITERS_WITH_WEIGHT);
    unsigned char *pBufferTail = LogGen_writeRecord(log_time, pLpw, pLogRecord);

    fwrite(buffer, pBufferTail - buffer, 1, stdout);
    log_time = add_random_ms(&log_time, 10, 2000);

  } while(++i < c_sample_data_num);

  return 0;
}
