#include <stdlib.h>
#include <time.h>
#include "log.h"
#include "log_generator.h"

unsigned char *LogGen_writeRecord(
  struct timespec log_time,
  const LogPayloadWriter *lpw,
  LogRecord *buffer
)
{
    return Log_writeRecord(log_time, lpw->kind, lpw->writer, lpw->arg, buffer);
}

/************************************************************
 * @brief 確率情報の総和を得る。

 * @note
 *  - 指定されたデータ配列の要素を操作し総和を得ます。
 *
 * @pram[in] 配列
 * @pram[in] 配列要素数
 * @return 確率情報の総和
 ************************************************************/
int LPWSWW_getTotalWeight(const LogPayloadWriterWithWeight *lpws_ww, int num)
{
  int total_weight = 0;
  for(int i = 0; i < num; i++)
  {
    total_weight += lpws_ww[i].weight;
  }

  return total_weight;
}

/************************************************************
 * @brief ログレコードへの書き込み関数をランダムに返します。

 * @note
 *
 * @pram[in] 配列
 * @pram[in] 要素数
 * @return 書き込み関数
 ************************************************************/
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
