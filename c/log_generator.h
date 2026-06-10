#ifndef LOG_GENERATOR_H
#define LOG_GENERATOR_H

#include <time.h>
#include "log.h"

/************************************************************
 * @struct LogPayloadWriter
 * @brief LogRecordへのデータ書き込みを制御する構造体
 *
 * @note
 *  本構造体で以下への書き込みを制御する。
 *    - `header.kind`
 *    - `payload`
 ************************************************************/
typedef struct logPayloadWriter
{
  char kind[4]; /**< 種別 : 4桁英数字 */
  unsigned char* (*writer)(const void *, unsigned char *); /**< 書込み関数 */
  void *arg; /** writer関数 第1引数 */
} LogPayloadWriter;

unsigned char *LogGen_writeRecord(struct timespec log_time, const LogPayloadWriter *lpw, LogRecord *buffer);
struct timespec LogGen_nextTime(const struct timespec *ts);

#endif
