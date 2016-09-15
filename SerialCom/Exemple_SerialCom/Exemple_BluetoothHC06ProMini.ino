#include <SerialCom.h>

int baudRate=9600; //banda de dados
char first='@';//caractere inicial da string 
char last='#';//caractere final

SerialCom bt(baudRate, first, last);
  
void setup() {
  Serial.begin(baudRate);
  bt.Send("ola");//envia "ola"
}

void loop() {
  String recieve=bt.getString();
  if(recieve!="null"){//bt.getString() retorna null se demorar muito tempo
    bt.Send(recieve);
    delay(100);
  }
}