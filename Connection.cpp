/**
 * @file Connection.cpp
 * @brief
 * @author Travis Lane
 * @version 0.0.1
 * @date 2016-01-05
 */

#include "Connection.h"

Connection::Connection(Bluetooth &new_bt) : bt(new_bt)
{
}

int Connection::write(int percent)
{
  char buff[4];
  char *c = buff;
  int rc = 0;

  if (!bt.connected()) {
    rc = -1;
    goto out;
  }

  rc = percent_to_str(percent, buff);
  if (rc != 0)
    goto out;

  bt.write((uint8_t *)buff, sizeof(buff));

out:
  return rc;
}

int Connection::read(int *out_percent)
{
  char buff[4];
  char c;
  int rc = 0, len = 0;

  if (!bt.connected()) {
    rc = -1;
    goto out;
  }

  if (bt.available() < 4) {
    rc = -2;
    goto out;
  }

  for (int i = 0; i < 4; i++) {
    buff[i] = bt.read();
    if (buff[i] == '\n' && i != 3) {
      rc = -3;
      goto out;
    }
  }

  rc = str_to_percent(buff, out_percent);
out:
  return rc;
}

int Connection::percent_to_str(int percent, char *out_str)
{
  int hundreds, tens, ones;
  if (percent < 0 || percent > 100) {
    out_str[0] = '\0';
    return -1;
  }

  hundreds = percent / 100;
  tens = (percent - (hundreds * 100)) / 10;
  ones = percent - (tens * 10);

  out_str[0] = '0' + hundreds;
  out_str[1] = '0' + tens;
  out_str[2] = '0' + ones;
  out_str[3] = '\n';
  return 0;
}

int Connection::str_to_percent(char *str, int *out_percent)
{
  int percent = 0;

  percent += (str[0] - '0') * 100;
  percent += (str[1] - '0') * 10;
  percent += (str[2] - '0');

  if (percent > 100 || percent < 0)
    return -1;

  return percent;
}
