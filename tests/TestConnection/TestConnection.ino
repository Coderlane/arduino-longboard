#include <ArduinoUnit.h>

#include <TestBluetooth.h>
#include <Connection.h>

TestSerial testSerial;
TestBluetooth bluetooth(testSerial, 0, "TestBluetooth");
Connection connection(bluetooth, 1);

test(send_recv)
{
  int rc, percent = 25, out_percent = 0;

  rc = connection.write(percent);
  assertMoreOrEqual(rc, 0);

  rc = connection.read(&out_percent);
  assertMoreOrEqual(rc, 0);

  assertEqual(percent, out_percent);
}

void setup()
{
  Serial.begin(9600);
  while(!Serial); // for the Arduino Leonardo/Micro only

  bluetooth.setup();
}

void loop()
{
  Test::run();
}
