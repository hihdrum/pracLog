#ifndef LOG_TIME_H
#define LOG_TIME_H

#include <time.h>

struct timespec normalize_timespec(const struct timespec *ts);
struct timespec parse_date_time(const char *str);
const char *log_date_time(const struct timespec *ts);
int get_next_increment_ms(int min, int max);
struct timespec add_random_ms(const struct timespec *ts, int min, int max);

#endif
