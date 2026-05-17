#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "log.h"
#include "log_time.h"

/************************************************************
 * @brief バッファにログレコードを書き込みます。

 * @note
 *  - ペイロードへの書き込みはWriterで指定した関数で行います。
 *  - バッファにはデータ書き込みに十分なサイズがある想定としており、
 *    サイズチェックは行っていません。
 *
 * @pram[in] ログレコードの日付・時刻
 * @pram[in] Writer
 * @pram[out] 書き込み先バッファアドレス
 * @return 書き込み後のバッファアドレス
 ************************************************************/
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
