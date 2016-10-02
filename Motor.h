/**
 * @file Motor.h
 * @brief
 * @author Travis Lane
 * @version
 * @date 2016-10-02
 */

#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
protected:
  int pin;
  int mppm;

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
  Motor(int pin, float mppm = 0.02f);
  void setup();

  void process();
  void request(int percent);
  int get_percent();
};

#endif /* MOTOR_H */
