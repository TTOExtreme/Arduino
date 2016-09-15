//#include <SerialCom.h>
#include <TCode.h>
TCode tc;

void setup() {
  Serial.begin(9600);
  tc.Init();
}

void loop() {
  tc.Exec();
}
