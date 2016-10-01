#include <Arduino.h>
#include <Throttle.h>

#define LOW_RESISTANCE 10 // 10 Ohms measured
#define HIGH_RESISTANCE 60 // 60 Ohms measured
#define REFERENCE_VOLTAGE 3.3 // 3.3V

const int high_throttle_value = 1023;
const int low_throttle_value = 0;

//Must be analog pin
const int throttle_pin = 23;   // A5

long cur_millis = 0;
long prev_millis = 0;
long interval_millis = 250;

Throttle throttle(throttle_pin, low_throttle_value, high_throttle_value);

void setup()
{
  Serial.begin(9600);
}

void loop ()
{
  cur_millis = millis();
  if (cur_millis - prev_millis > interval_millis) {
    prev_millis = cur_millis;
    Serial.println(throttle.read());
  }
}
