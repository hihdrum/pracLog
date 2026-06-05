#ifndef LOG_TIME_H
#define LOG_TIME_H

#include <time.h>

#define NS_PER_MS     1000000L /**< [ナノ秒/ミリ秒] */
#define NS_PER_SEC 1000000000L /**< [ナノ秒/秒] */

struct timespec LogTime_normalize(const struct timespec *ts);
struct timespec LogTime_parseDateTime(const char *str);
const char *log_date_time(const struct timespec *ts);
struct timespec add_random_ms(const struct timespec *ts, int min, int max);

#endif
