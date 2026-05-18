#include <stdio.h>
#include <string.h>
#include <time.h>

#include "log.h"
#include "log_time.h"

unsigned char *LOG_writeRecord(
  const struct timespec log_time,
  const char *kind,
  unsigned char *(*recordWriter)(const void *, unsigned char *),
  const void *arg,
  LogRecord *buffer)
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

#if 0
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
#endif

unsigned char *write_LogRecord(struct timespec log_time, const LogPayloadWriter *lpw, LogRecord *buffer)
{
    return LOG_writeRecord(log_time, lpw->kind, lpw->writer, NULL, buffer);
}
