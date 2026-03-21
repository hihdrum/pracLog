#include <stdio.h>
#include <stdlib.h>
#include "log_time.h"

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
