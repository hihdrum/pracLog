#ifndef LOG_H
#define LOG_H

#pragma pack(push, 1)

/************************************************************
 * @struct LogHeader
 * @brief ログヘッダのバイト構造を表現する構造体
 ************************************************************/
typedef struct logHeader
{
  char date[8]; /**< 日付情報 : yyyymmdd */
  char time[9]; /**< 時刻情報 : HHMMSSsss */
  char kind[4]; /**< 種別 : 4桁英数字 */
  char size[8]; /**< ペイロードサイズ数字文字 */
} LogHeader;

/************************************************************
 * @struct LogRecord
 * @brief ログレコードのバイト構造を表現する構造体
 *
 * @note
 *  - `payload`のサイズは、`header.size`とする。
 ************************************************************/
typedef struct logRecord
{
  LogHeader header;         /**< ヘッダ */
  unsigned char payload[0]; /**< ペイロード */
} LogRecord;

#pragma pack(pop)

unsigned char *Log_writeRecord(const struct timespec log_time, const char *kind, unsigned char *(*writer)(const void *, unsigned char *), const void *arg, LogRecord *buffer);

#endif
