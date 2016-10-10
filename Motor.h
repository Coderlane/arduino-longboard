/**
 * @file Motor.h
 * @brief
 * @author Travis Lane
 * @version
 * @date 2016-10-02
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <Servo.h>

class Motor
{
protected:
  Servo esc;
  int pin;
  int macc;
  int mdec;

  // Timing
  long last_millis = 0;
  long next_millis = 0;
  int interval = 100;

  // Request handling
  int req_percent = 0;
  int cur_percent = 0;

  void set_percent(int percent);
  int percent_to_val(int percent);
  int next_percent(long milli);

public:
  Motor(int pin, int macc, int mdec);
  void setup();
  void setup_millis(long cur_millis);

  void process();
  void process_millis(long cur_millis);

  void request(int percent);
  int get_percent();
};

#endif /* MOTOR_H */
