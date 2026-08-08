#ifndef LOG_H
#define LOG_H

/************************************************************
 * @file log.h
 * @brief ログレコードのバイナリ構造定義
 * @note このファイルは ../spec/log-record-spec.yaml で定義された
 *       仕様に従って実装されています。
 *       詳細な仕様はそのファイルを参照してください。
 ************************************************************/

#pragma pack(push, 1)

/************************************************************
 * @struct LogHeader
 * @brief ログヘッダのバイト構造を表現する構造体
 * @note 固定サイズ: 29バイト (8+9+4+8)
 * @see ../spec/log-record-spec.yaml
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
 * @note
 *  - `payload`のサイズは、`header.size`とする。
 *  - 固定ヘッダ: 29バイト、可変長ペイロード: header.sizeから決定する。
 * @see ../spec/log-record-spec.yaml
 **/
typedef struct logRecord
{
  LogHeader header;         /**< ヘッダ */
  unsigned char payload[0]; /**< ペイロード */
} LogRecord;

#pragma pack(pop)

const char *Log_toHeaderDateTime(const struct timespec *ts);

unsigned char *Log_writeRecord(const struct timespec log_time, const char *kind,
  unsigned char *(*writer)(const void *, unsigned char *), const void *arg, LogRecord *buffer);

#endif
