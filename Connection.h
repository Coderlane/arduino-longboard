/**
 * @file Connection.h
 * @brief
 * @author Travis Lane
 * @version 0.0.1
 * @date 2016-01-05
 */

#include "Bluetooth.h"

#include <ArduinoJson.h>

enum ConnectionStatus { CONN_UP, CONN_DOWN};

class Connection {
public:
  Connection(Bluetooth &new_bt, int id);

  int write(int percent);
  int read(int *out_percent);

private:
  int id;
  Bluetooth &bt;
};
