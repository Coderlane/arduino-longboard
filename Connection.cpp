/**
 * @file Connection.cpp
 * @brief
 * @author Travis Lane
 * @version 0.0.1
 * @date 2016-01-05
 */

#include "Connection.h"

Connection::Connection(Bluetooth &new_bt, int id) : bt(new_bt)
{
  this->id = id;
}

int Connection::write(int percent)
{
  int rc = 0;
  StaticJsonBuffer<200> buffer;
  JsonObject& object = buffer.createObject();

  if (!bt.connected()) {
    return -1;
  }

  object["id"] = this->id;
  object["throttle"] = percent;

  /* Don't pretty print, I deliminate on \n */
  rc = object.printTo(bt);
  bt.write('\n');

  return rc;
}

int Connection::read(int *out_percent)
{
  int rc = 0;
  char buff[200];
  StaticJsonBuffer<200> buffer;

  if (!bt.connected()) {
    return -1;
  }

  rc = bt.readBytesUntil('\n', buff, sizeof(buff));
  if (rc <= 0) {
    return -1;
  }

  /* Set last char to NULL */
  buff[rc] = '\0';

  JsonObject& object = buffer.parseObject(buff);

  if (!object.success()) {
    return -1;
  }

  if (object["id"] != id) {
    /* The ID doesn't match... We should ignore this message */
    return -1;
  }

  *out_percent = object["throttle"];
  return rc;
}
