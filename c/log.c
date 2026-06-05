#include <stdio.h>
#include <string.h>
#include <time.h>

#include "log.h"
#include "log_time.h"

/************************************************************
 * @brief ログレコード(日付情報,時刻情報)変換処理
 *
 * @note
 *  - struct timespecをLogRecordのdate,timeに変換します。
 *  - 変換データは静的バッファで保持しています。
 *
 * @pram[in] 日付・時刻情報
 * @return 変換データ保持アドレス
 ************************************************************/
const char *Log_toHeaderDateTime(const struct timespec *ts)
{
  struct tm *lt = localtime(&ts->tv_sec);

  static char retStr[64];
  size_t milliSecondsIndex = strftime(retStr, sizeof(retStr), "%Y%m%d%H%M%S", lt);
  sprintf(&retStr[milliSecondsIndex], "%03ld", ts->tv_nsec / NS_PER_MS);

  return retStr;
}

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
unsigned char *Log_writeRecord(
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

    strcpy((char *)pLogHeader, Log_toHeaderDateTime(&log_time));
    memcpy(pLogHeader->kind, kind, sizeof(pLogHeader->kind));

    memcpy(&pLogRecord->header.size, sizeBuffer,
      sizeof(pLogRecord->header.size));

  return pBufferTail;
}
