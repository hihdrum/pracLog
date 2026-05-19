#include <time.h>
#include "log.h"
#include "log_generator.h"

unsigned char *write_LogRecord(struct timespec log_time, const LogPayloadWriter *lpw, LogRecord *buffer)
{
    return LOG_writeRecord(log_time, lpw->kind, lpw->writer, NULL, buffer);
}
