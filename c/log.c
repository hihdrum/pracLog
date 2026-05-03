#include <stdio.h>
#include <string.h>
#include <time.h>

#include "log.h"
#include "log_time.h"

/************************************************************
 * @brief バッファにログレコードを書き込みます。

 * @note
 *  - ログレコードのペイロードはWriterで指定した関数で行われます。
 *  - バッファにはデータ書き込みに十分なサイズがある想定で動作します。
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
