#include <stdio.h>
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
 * @pram[in] 種別
 * @pram[in] Writer関数
 *           本関数の引数は以下が指定される想定である。
 *             第1引数 : writer関数向けの引数
 *             第2引数 : 書き込み先バッファアドレス
 * @pram[in] Writer関数の引数
 *           - Writer関数の第1引数となる。
 * @pram[out] 書き込み先バッファアドレス
 *            - Writer関数の第2引数となる。
 * @return 書き込み後のバッファアドレス
 ************************************************************/
unsigned char *LOG_writeRecord(
  const struct timespec log_time,
  const char *kind,
  unsigned char *(*recordWriter)(const void *writerArg, unsigned char *targetBuffer),
  const void *arg,
  LogRecord *buffer
)
{
    LogRecord *pLogRecord = buffer;
    LogHeader *pLogHeader = &pLogRecord->header;

    unsigned char *pKindHeader = pLogRecord->payload;
    unsigned char *pBufferTail = recordWriter(arg, pKindHeader);

    char sizeBuffer[9];
    snprintf(sizeBuffer, sizeof(sizeBuffer), "%08ld", pBufferTail - pKindHeader);

    strcpy((char *)pLogHeader, log_date_time(&log_time));
    memcpy(pLogHeader->kind, kind, sizeof(pLogHeader->kind));

    memcpy(&pLogRecord->header.size, sizeBuffer,
      sizeof(pLogRecord->header.size));

  return pBufferTail;
}
