/**
 * @file Throttle.cpp
 * @brief
 * @author Travis Lane
 * @version 0.1.0
 * @date 2015-03-04
 */

#include "Throttle.h"
#include "Arduino.h"

/*
 * @brief Creates a new throttle.
 *
 * @param new_pin The pin to read from.
 * @param new_min (Optional) The minimum value. Defaults to 0.
 * @param new_max (Optional) The maximum value. Defaults to 1023.
 */
Throttle::Throttle(int new_pin, int new_min, int new_max)
{
  pin = new_pin;

  min = new_min;
  max = new_max;
  range = max - min;
}

/**
 * @brief read the percentage value from the pin.
 *
 * @return A percentage. 0 to 100 as an integer.
 */
int Throttle::read()
{
  int val = analogRead(pin);

  if(val <= min) {
    // Low range;
    return 0;
  }

  if(val >= max) {
    // High range
    return 100;
  }

  val -= min; // Shift downward
  return val / range; // Compute result
}
