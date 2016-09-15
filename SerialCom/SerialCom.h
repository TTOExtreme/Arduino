/*/
     Created by TTOExtreme in 18-05-2016
/*/

#ifndef SerialCom_h
#define SerialCom_h

#include "Arduino.h"

class SerialCom {
  public:
    //SerialCom();
    //SerialCom(int BaudRate);
    SerialCom(int BaudRate, char cFirst, char cLast);
	void set(int BaudRate);
	void set(int BaudRate, char cFirst, char cLast);
	void setTimeFeedback(int timeFeedback);
	void setFeedback(char Feedback);
	void Send(String mess);
    String getString();
    char getChar();

  private:
	int _hasFeedback=0;
	char _Feedback;
	int _timeFeedback=500;

	int _BaudRate=9600;
	
	int _hasString=0;//para indicar se existe caractere final e inicial
	char _cFirst;
	char _cLast;
};

#endif
