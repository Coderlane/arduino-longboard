/**
 * @file Throttle.h
 * @brief 
 * @author Travis Lane
 * @version 0.1.0
 * @date 2015-03-04
 */

#ifndef THROTTLE_H
#define THROTTLE_H

#define THROTTLE_DEFAULT_MIN 0
#define THROTTLE_DEFAULT_MAX 1023

class Throttle
{
private:
  int pin;
  int min;
  int max;

public:
  Throttle(int new_pin,
           int new_min = THROTTLE_DEFAULT_MIN,
           int new_max = THROTTLE_DEFAULT_MAX);

  void setMin(int new_min);
  void setMax(int new_max);

  int read();
};

#endif /* THROTTLE_H */
