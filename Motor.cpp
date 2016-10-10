#include <Arduino.h>
#include "Motor.h"

/**
 * @brief Create a new motor that regulates speed evenly.
 *
 * @param pin The pin of the motor.
 * @param macc maximum percent power change (positive) per interval.
 * @param mdec maximum percent power change (negative) per interval.
 */
Motor::Motor(int pin, int macc, int mdec)
{
  this->pin = pin;
  this->macc = macc;
  this->mdec = mdec;
}

void Motor::setup()
{
  setup_millis(millis());
}

void Motor::setup_millis(long cur_millis)
{
  esc.attach(pin);

  // Start at a stop
  set_percent(0);

  // Setup timing
  last_millis = cur_millis;
  next_millis = last_millis + interval;
}

void Motor::process()
{
  process_millis(millis());
}

void Motor::process_millis(long cur_millis)
{
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
  int diff = req_percent - cur_percent;
  int mchange;

  if (diff < 0) {
    /* Decrease power */
    mchange = mdec;
  } else {
    /* Increase power */
    mchange = macc;
  }

  /**
   * TODO: This could probably scale the next percent based on
   * the current interval. IE: If we had a double interval for
   * some reason maybe this should return double the maximum change.
   */

  if (abs(diff) < mchange) {
    // Difference is less than max, simply use the difference.
    return req_percent;
  }

  // Difference is greater than the max.
  if (diff < 0) {
    return max(cur_percent - mchange, 0);
  } else {
    return min(cur_percent + mchange, 100);
  }
}

int Motor::get_percent()
{
  return cur_percent;
}

void Motor::set_percent(int percent)
{
  int val = map(percent, 0, 100, 1200, 2000);
  esc.writeMicroseconds(val);
  cur_percent = percent;
}
