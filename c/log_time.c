#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "randInt.h"
#include "log_time.h"

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
struct timespec LogTime_normalize(const struct timespec *ts)
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
struct timespec LogTime_parseDateTime(const char *str)
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
 * @brief 指定した日付・時刻情報にランダム値を加算したものを返します。
 *
 * @pram[in] 日付・時刻情報
 * @pram[in] 最小値
 * @pram[in] 最大値
 * @return 日付・時刻情報
 ************************************************************/
struct timespec LogTime_addRandomMS(const struct timespec *ts, int min, int max)
{
    struct timespec next_ts = *ts;
    long inc_ms = random_range(min, max);

    next_ts.tv_nsec += (inc_ms * NS_PER_MS);
    return LogTime_normalize(&next_ts);
}
