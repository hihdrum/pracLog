#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "log.h"
#include "f001data.h"
#include "f002data.h"
#include "f003data.h"
#include "log_time.h"

typedef struct
{
  LogPayloadWriter writer;
  int weight;
} LogPayloadWriterWithWeight;

const LogPayloadWriterWithWeight lpws_ww[] = {
  { .writer = { .kind = "F001", .writer = write_F001_D001_data }, .weight = 30 },
  { .writer = { .kind = "F001", .writer = write_F001_D002_data }, .weight = 25 },
  { .writer = { .kind = "F002", .writer = write_F002_D001_data }, .weight = 25 },
  { .writer = { .kind = "F003", .writer = write_F003_D01_data },  .weight = 30 },
};

#define D_LOG_PAYLOAD_WRITERS_WITH_WEIGHT (sizeof(lpws_ww)/sizeof(lpws_ww[0]))

int LPWSWW_getTotalWeight(const LogPayloadWriterWithWeight *lpws_ww, int num)
{
  int total_weight = 0;
  for(int i = 0; i < num; i++)
  {
    total_weight += lpws_ww[i].weight;
  }

  return total_weight;
}

const LogPayloadWriter *LPSWW_randLogPayloadWriter(const LogPayloadWriterWithWeight *lpws_ww, int num)
{
  int total_weight = LPWSWW_getTotalWeight(lpws_ww, num);

  int rand_val = rand() % total_weight;
  int cumsum = 0;
  int typeD = 0;

  for(int i = 0; i < num; i++)
  {
    cumsum += lpws_ww[i].weight;
    if(rand_val < cumsum)
    {
      typeD = i;
      break;
    }
  }

  return &lpws_ww[typeD].writer;
}

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

    const LogPayloadWriter *pLpw = LPSWW_randLogPayloadWriter(lpws_ww, D_LOG_PAYLOAD_WRITERS_WITH_WEIGHT);
    unsigned char *pBufferTail = write_LogRecord(log_time, pLpw, pLogRecord);

    fwrite(buffer, pBufferTail - buffer, 1, stdout);
    log_time = add_random_ms(&log_time, 10, 2000);

  } while(++i < c_sample_data_num);

  return 0;
}
