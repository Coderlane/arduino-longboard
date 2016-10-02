

#include <Arduino.h>
#include "Motor.h"

/**
 * @brief Create a new motor that regulates speed evenly.
 *
 * @param pin The pin of the motor.
 * @param mppm maximum percent per millisecond, The maximum percent change
 * in power per millisecond default is .02 which works out to 20%
 * power per second.
 */
Motor::Motor(int pin, float mppm)
{
  this->pin = pin;
  this->mppm = mppm;
}

void Motor::setup()
{
  pinMode(pin, OUTPUT);

  // Start at a stop
  set_percent(0);

  // Setup timing
  last_millis = millis();
  next_millis = last_millis + interval;
}

void Motor::process()
{
  long cur_millis = millis();
  if ((cur_millis - next_millis) >= 0) {
    // Time is up, calculate the next value
    int percent = next_percent(last_millis - cur_millis);
    if (percent != get_percent()) {
      set_percent(percent);
    }

    // Update the timers
    last_millis = cur_millis;
    next_millis = cur_millis + interval;
  }
}

void Motor::request(int percent)
{
  req_percent = percent;
}

int Motor::next_percent(long milli)
{
  int diff = abs(cur_percent - req_percent);
  if (((float) diff / (float) milli) < mppm) {
    // Difference is less than max, simply use the difference.
    return req_percent;
  }

  // Calculate the maximum change and return the new percent.
  diff = (float)milli * mppm;
  if (cur_percent > req_percent) {
    return cur_percent - diff;
  } else {
    return cur_percent + diff;
  }
}

int Motor::get_percent()
{
  return cur_percent;
}

void Motor::set_percent(int percent)
{
  analogWrite(pin, percent_to_val(percent));
  cur_percent = percent;
}

int Motor::percent_to_val(int percent)
{
  // Scale from 0 to 100 to 0 to 255
  return (100.0f / 255.0f) * (float) percent;
}
