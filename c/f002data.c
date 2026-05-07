#include <string.h>

#include "randInt.h"
#include "f002data.h"

unsigned char *write_F002_D001_data(unsigned char *buffer)
{
  F002_Header *pF002Header = (F002_Header *)buffer;
  F002_D001 *pF002_D001 = (F002_D001 *)pF002Header->data;

  int8_t len = random_range(0, D_F002_D001_MAX_MSG_LEN);
  char message_char = random_range('A', 'Z');

  pF002_D001->len = len;
  memset(pF002_D001->message, ' ', D_F002_D001_MAX_MSG_LEN);
  memset(pF002_D001->message, message_char, len);

  *pF002Header = (F002_Header){ .type = "D001" };

  return (unsigned char *)&pF002_D001->message[D_F002_D001_MAX_MSG_LEN];
}
