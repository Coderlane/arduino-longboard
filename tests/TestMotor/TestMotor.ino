#include <ArduinoUnit.h>

#include <Motor.h>

const int motor_pin = 10; // D10

test(motor_acceleration)
{
  Motor motor(motor_pin, /* acc */ 5, /* dec */ 10);
  int cur_millis = 0;

  // Setup the motor
  motor.setup_millis(cur_millis);
  assertEqual(motor.get_percent(), 0);

  // Request an odd amount of power
  motor.request(7);
  assertEqual(motor.get_percent(), 0);

  // Run through one cycle
  motor.process_millis((cur_millis += 100));
  assertEqual(motor.get_percent(), 5);

  // Run half a cycle
  motor.process_millis((cur_millis += 50));
  assertEqual(motor.get_percent(), 5);

  // Finish the cycle
  motor.process_millis((cur_millis += 51));
  assertEqual(motor.get_percent(), 7);
}


test(motor_deceleration)
{
  Motor motor(motor_pin, /* acc */ 100, /* dec */ 10);
  int cur_millis = 0;

  // Setup the motor
  motor.setup_millis(cur_millis);
  assertEqual(motor.get_percent(), 0);

  // Request full power
  motor.request(100);
  assertEqual(motor.get_percent(), 0);

  // Run through one cycle
  motor.process_millis((cur_millis += 100));
  assertEqual(motor.get_percent(), 100);


  // Request half power
  motor.request(50);
  assertEqual(motor.get_percent(), 100);
  
  motor.process_millis((cur_millis += 100));
  assertEqual(motor.get_percent(), 90);
}

void setup()
{
  Serial.begin(9600);
  while(!Serial); // for the Arduino Leonardo/Micro only
}

void loop()
{
  Test::run();
}
