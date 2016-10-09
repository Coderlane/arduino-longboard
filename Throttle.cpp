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
}

/**
 * @brief read the percentage value from the pin.
 *
 * @return A percentage. 0 to 100 as an integer.
 */
int Throttle::read()
{
  int out;
  int val = analogRead(pin);

  out = map(val, min, max, 0, 100);

  // Normalize the values
  if (out > 100) {
    out = 100;
  } else if (out < 0) {
    out = 0;
  }

  return out;
}

/**
 * @brief Set the minimum value for the throttle.
 *
 * @param new_min The new minimum value.
 */
void Throttle::setMin(int new_min)
{
  min = new_min;
}

/**
 * @brief Set the new maximum value for the throttle.
 *
 * @param new_max The new maximum value.
 */
void Throttle::setMax(int new_max)
{
  max = new_max;
}
