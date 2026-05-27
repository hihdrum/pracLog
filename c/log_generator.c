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
