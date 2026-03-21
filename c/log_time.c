#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NS_PER_MS     1000000L // [ナノ秒/ミリ秒]
#define NS_PER_SEC 1000000000L // [ナノ秒/秒]

/**
 * ナノ秒部分が1秒を超えている場合に秒を繰り上げる。
 * 戻り値 : 繰上げ処理済み struct timespec
 */
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

/**
 * YYYY/mm/dd HH:MM:SS.sss形式の文字列をstruct timespecに
 * 変換する。
 */
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

/**
 * struct timespecをログの時刻フォーマットに変換する。
 * @return 変換フォーマット文字列へのポインタ(注 : 静的バッファ)
 */
const char *log_date_time(const struct timespec *ts)
{
  struct tm *lt = localtime(&ts->tv_sec);

  static char retStr[64];
  size_t milliSecondsIndex = strftime(retStr, sizeof(retStr), "%Y%m%d%H%M%S", lt);
  sprintf(&retStr[milliSecondsIndex], "%03ld", ts->tv_nsec / NS_PER_MS);

  return retStr;
}

/**
 * @return min <= x <= max の範囲の乱数値
 */
int get_next_increment_ms(int min, int max)
{
  return (rand() % (max - min + 1)) + min;
}

struct timespec add_random_ms(const struct timespec *ts, int min, int max)
{
    struct timespec next_ts = *ts;
    long inc_ms = get_next_increment_ms(min, max);

    next_ts.tv_nsec += (inc_ms * NS_PER_MS);
    return normalize_timespec(&next_ts);
}

int main()
{
  const char *start_time = "2026/01/02 11:22:33.444";
  struct timespec current_ts = parse_date_time(start_time);

  srand(0);

  printf("--- Generating Monotic Increasing Data --\n");

  struct timespec next_ts = current_ts;
  for(int i = 0; i < 10; i++)
  {
    next_ts = add_random_ms(&next_ts, 100, 1500);
    printf("[%02d] %s\n", i + 1, log_date_time(&next_ts));
  }

  return 0;
}
