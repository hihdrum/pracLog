#ifndef LOG_GENERATOR
#define LOG_GENERATOR

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
  unsigned char* (*writer)(unsigned char *); /**< 書込み関数 */
} LogPayloadWriter;

/************************************************************
 * @struct LogPayloadWriterWithWeight
 * @brief LogRecordへのデータ書き込みを制御する構造体と確率情報
 *
 * @note
 *  本構造体で以下への書き込みを制御する。
 *    - `header.kind`
 *    - `payload`
 ************************************************************/
typedef struct
{
  LogPayloadWriter writer;
  int weight;
} LogPayloadWriterWithWeight;

unsigned char *write_LogRecord(struct timespec log_time, const LogPayloadWriter *lpw, LogRecord *buffer);
int LPWSWW_getTotalWeight(const LogPayloadWriterWithWeight *lpws_ww, int num);
const LogPayloadWriter *LPSWW_randLogPayloadWriter(const LogPayloadWriterWithWeight *lpws_ww, int num);

#endif
