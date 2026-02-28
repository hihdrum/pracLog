#ifndef LOG_H
#define LOG_H

#pragma pack(push, 1)
typedef struct logHeader
{
  char date[8]; /* 日付情報 : yyyymmdd */
  char time[9]; /* 時刻情報 : HHMMSSsss */
  char kind[4]; /* 種別 : 4桁英数字 */
  char size[8]; /* ペイロードサイズ数字文字 */
} LogHeader;

typedef struct logRecord
{
  LogHeader header; /* ヘッダ */
  unsigned char payload[0]; /* ペイロード */
} LogRecord;

#pragma pack(pop)

#endif
