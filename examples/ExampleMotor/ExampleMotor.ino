#include <Arduino.h>
#include <Motor.h>

//Must be analog pin w/ PWM
const int motor_pin = 6;   // A7

long cur_millis = 0;
long prev_millis = 0;
long interval_millis = 1000;

Motor motor(motor_pin, 5, 6);

void setup()
{
  Serial.begin(9600);
  motor.setup();
}

void loop ()
{
  cur_millis = millis();
  motor.process();
  if (cur_millis - prev_millis > interval_millis) {
    int req = random(0, 100);

    Serial.print("Requesting: ");
    Serial.println(req);

    Serial.print("Currently: ");
    Serial.println(motor.get_percent());

    motor.request(random(0, 100));
  }
}
