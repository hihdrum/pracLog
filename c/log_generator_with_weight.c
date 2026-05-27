#include <stdlib.h>
#include <time.h>
#include "log_generator.h"
#include "log_generator_with_weight.h"

/************************************************************
 * @brief 確率情報の総和を得る。

 * @note
 *  - 指定されたデータ配列の要素を操作し総和を得ます。
 *
 * @param[in] 配列
 * @param[in] 配列要素数
 * @return 確率情報の総和
 ************************************************************/
int LGWW_getTotalWeight(const LogPayloadWriterWithWeight *lpws_ww, int num)
{
  int total_weight = 0;
  for(int i = 0; i < num; i++)
  {
    total_weight += lpws_ww[i].weight;
  }

  return total_weight;
}

/************************************************************
 * @brief ログレコードへの書き込み関数をランダムに返します。

 * @note
 *
 * @param[in] 配列
 * @param[in] 要素数
 * @return 書き込み関数
 ************************************************************/
const LogPayloadWriter *LGWW_getRandomLogPayloadWriter(
  const LogPayloadWriterWithWeight *lpws_ww,
   int num
)
{
  int total_weight = LGWW_getTotalWeight(lpws_ww, num);

  int rand_val = rand() % total_weight;
  int cumsum = 0;
  int typeD = 0;

  for(int i = 0; i < num; i++)
  {
    cumsum += lpws_ww[i].weight;
    if(rand_val < cumsum)
    {
      typeD = i;
      break;
    }
  }

  return &lpws_ww[typeD].writer;
}
