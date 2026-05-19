#include <time.h>
#include "log.h"
#include "log_generator.h"

unsigned char *LogGen_writeRecord(
  struct timespec log_time,
  const LogPayloadWriter *lpw,
  LogRecord *buffer
)
{
    return Log_writeRecord(log_time, lpw->kind, lpw->writer, NULL, buffer);
}
