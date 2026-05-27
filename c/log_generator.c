#include <stdlib.h>
#include <time.h>
#include "log.h"
#include "log_generator.h"

/************************************************************
 * @brief バッファにログレコードを書き込みます。

 * @note
 *  - LogGen層のログレコード書き込み関数
 *
 * @pram[in] ログレコードの日付・時刻
 * @pram[in] ログレコード書き込み制御構造体
 * @pram[in] Writer関数
 *           本関数の引数は以下が指定される想定である。
 *             第1引数 : writer関数向けの引数
 *             第2引数 : 書き込み先バッファアドレス
 * @pram[out] 書き込み先バッファアドレス
 * @return 書き込み後のバッファアドレス
 ************************************************************/
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
 * @param[in] 配列
 * @param[in] 配列要素数
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
 * @param[in] 配列
 * @param[in] 要素数
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
