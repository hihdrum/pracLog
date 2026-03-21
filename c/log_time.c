#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * ナノ秒部分が1秒を超えた場合に秒を繰り上げる。
 */
void normalize_timespec(struct timespec *ts)
{
  if(ts->tv_nsec >= 1000000000L)
  {
    /* 繰上げ処理を行う。*/
    ts->tv_sec += ts->tv_nsec / 1000000000L;
    ts->tv_nsec %= 1000000000L;
  }
}

struct timespec parse_time_str(const char *str)
{
  struct tm t = {0};
  long ms = 0;

  sscanf(str, "%4d/%2d/%2d %2d:%2d:%2d.%3ld",
    &t.tm_year, &t.tm_mon, &t.tm_mday,
    &t.tm_hour, &t.tm_min, &t.tm_sec, &ms);

  t.tm_year -= 1900;
  t.tm_mon -= 1;
  t.tm_isdst = -1;

  struct timespec ts;
  ts.tv_sec = mktime(&t);
  ts.tv_nsec = ms * 1000000L; /* ミリ秒 -> ナノ秒 */
  return ts;
}

void print_timespec(const struct timespec *ts)
{
  struct tm *lt = localtime(&ts->tv_sec);
  char buf[64];

  strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", lt);
  printf("%s%03ld\n", buf, ts->tv_nsec / 1000000L);
}

int main()
{
  const char *start_time = "2026/01/02 11:22:33.444";
  struct timespec current_ts = parse_time_str(start_time);

  srand(0);

  printf("--- Generating Monotic Increasing Data --\n");

  for(int i = 0; i < 10; i++)
  {
    long inc_ms = (rand() % 1401) + 100;

    current_ts.tv_nsec += (inc_ms * 1000000L);
    normalize_timespec(&current_ts);

    printf("[%02d] ", i + 1);
    print_timespec(&current_ts);
  }

  return 0;
}
