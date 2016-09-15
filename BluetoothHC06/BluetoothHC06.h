/*/
     Created by TTOExtreme in 18-05-2016
/*/

#ifndef BluetoothHC06_h
#define BluetoothHC06_h

#include "Arduino.h"

class BluetoothHC06 {
  public:
    BluetoothHC06(int PortSerial, int BaudRate);
    BluetoothHC06(int PortSerial, int BaudRate, char cFirst, char cLast);
	void setTimeFeedback(int timeFeedback);
	void setFeedback(char Feedback);
	void Send(String mess);
    String getString();
    char getChar();

  private:
	int _hasFeedback=0;
	char _Feedback;
	int _timeFeedback=500;
	
	int _PortSerial=0;
	int _BaudRate=9600;
	
	int _hasString=0;//para indicar se existe caractere final e inicial
	char _cFirst;
	char _cLast;
};

#endif
