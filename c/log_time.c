#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NS_PER_MS     1000000L /**< [ナノ秒/ミリ秒] */
#define NS_PER_SEC 1000000000L /**< [ナノ秒/秒] */

/************************************************************
 * @brief struct timespec ナノ秒部分の繰上げ処理を行います。
 *
 * @note ナノ秒部分が1秒を超えている場合、繰上げ処理を行った
 *       struct timespecを返します。
 * @pram[in] 日付・時刻情報
 * @return 繰上げ処理後のstruct timespec
 *
 * @note 記述した説明がイマイチである。
 ************************************************************/
struct timespec normalize_timespec(const struct timespec *ts)
{
  struct timespec ret = *ts;

  if(ret.tv_nsec >= NS_PER_SEC)
  {
    ret.tv_sec += ts->tv_nsec / NS_PER_SEC;
    ret.tv_nsec = ts->tv_nsec % NS_PER_SEC;
  }

  return ret;
}

/************************************************************
 * @brief struct timespec変換処理
 *
 * @note YYYY/mm/dd HH:MM:SS.sss形式の文字列をstruct timespecに変換します。
 * @param[in] 日付・時刻情報
 * @return struct timespec
 ************************************************************/
struct timespec parse_date_time(const char *str)
{
  int raw_year;
  int raw_mon;
  struct tm t = {0};
  long ms;

  sscanf(str, "%4d/%2d/%2d %2d:%2d:%2d.%3ld",
    &raw_year, &raw_mon, &t.tm_mday,
    &t.tm_hour, &t.tm_min, &t.tm_sec, &ms);

  t.tm_year = raw_year - 1900;
  t.tm_mon  = raw_mon - 1;
  t.tm_isdst = -1;

  struct timespec ret = { .tv_sec = mktime(&t), .tv_nsec = ms * NS_PER_MS };
  return ret;
}

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
const char *log_date_time(const struct timespec *ts)
{
  struct tm *lt = localtime(&ts->tv_sec);

  static char retStr[64];
  size_t milliSecondsIndex = strftime(retStr, sizeof(retStr), "%Y%m%d%H%M%S", lt);
  sprintf(&retStr[milliSecondsIndex], "%03ld", ts->tv_nsec / NS_PER_MS);

  return retStr;
}

/************************************************************
 * @brief 指定範囲内の乱数を得ます。
 *
 * @pram[in] 最小値
 * @pram[in] 最大値
 * @return min <= int <= max
 ************************************************************/
int get_next_increment_ms(int min, int max)
{
  return (rand() % (max - min + 1)) + min;
}

/************************************************************
 * @brief 指定した日付・時刻情報にランダム値を加算したものを返します。
 *
 * @pram[in] 日付・時刻情報
 * @pram[in] 最小値
 * @pram[in] 最大値
 * @return 日付・時刻情報
 ************************************************************/
struct timespec add_random_ms(const struct timespec *ts, int min, int max)
{
    struct timespec next_ts = *ts;
    long inc_ms = get_next_increment_ms(min, max);

    next_ts.tv_nsec += (inc_ms * NS_PER_MS);
    return normalize_timespec(&next_ts);
}
