//#include <SerialCom.h>
#include <TCode.h>
TCode tc = new TCode("Bluetooth");//"Wifi"

void setup() {
  Serial.begin(9600);
  tc.Init();
}

void loop() {
  tc.Exec();
}
