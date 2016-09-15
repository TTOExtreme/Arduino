#include <BluetoothHC06.h>

int serialPort=3; //porta serial do modulo
int baudRate=9600; //banda de dados
char first='@';//caractere inicial da string 
char last='#';//caractere final

BluetoothHC06 bt(serialPort, baudRate, first, last);
  
void setup() {
  bt.Send("ola");//envia "ola"
}

void loop() {
  String recieve=bt.getString();
  if(recieve!="null"){//bt.getString() retorna null se demorar muito tempo
    bt.Send(recieve);
    delay(100);
  }
}
