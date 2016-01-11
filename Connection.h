/**
 * @file Connection.h
 * @brief
 * @author Travis Lane
 * @version 0.0.1
 * @date 2016-01-05
 */

#include "Bluetooth.h"

enum ConnectionStatus { CONN_UP, CONN_DOWN};

class Connection {
public:
  Connection(Bluetooth &new_bt);

  int write(int percent);
  int read(int *out_percent);

private:
  Bluetooth &bt;

  static int percent_to_str(int percent, char *out_str);
  static int str_to_percent(char *str, int *out_percent);
};
