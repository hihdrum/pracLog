#ifndef LOG_GENERATOR_WITH_WEIGHT_H
#define LOG_GENERATOR_WITH_WEIGHT_H

#include "log.h"

/************************************************************
 * @struct LogPayloadWriterWithWeight
 * @brief LogRecordへのデータ書き込みを制御する構造体と選択確率の重み情報を持つ。
 *
 * @note
 *  本構造体で`LogPayloadWriter`が選択される確率的な重み(`weight`)を制御する。
 ************************************************************/
typedef struct
{
  LogPayloadWriter writer;
  int weight;
} LogPayloadWriterWithWeight;

int LPWSWW_getTotalWeight(const LogPayloadWriterWithWeight *lpws_ww, int num);
const LogPayloadWriter *LPSWW_randLogPayloadWriter(const LogPayloadWriterWithWeight *lpws_ww, int num);

#endif
