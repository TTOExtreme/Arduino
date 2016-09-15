/*/
 *   Created by TTOExtreme in 18-05-2016
/*/

#include "Arduino.h"
#include "SerialCom.h"

SerialCom::SerialCom(int BaudRate, char cFirst, char cLast)
{
	_BaudRate=BaudRate;
	_cFirst=cFirst;
	_cLast=cLast;
	_hasFeedback=0;
	_hasString=1;
	
	Serial.begin(BaudRate);
}

void SerialCom::setTimeFeedback(int timeFeedback)
{
	_timeFeedback=timeFeedback;
}

void SerialCom::setFeedback(char Feedback)
{
	_Feedback=Feedback;
	_hasFeedback=1;
}

void SerialCom::Send(String mess)
{
	if(_hasFeedback==1){
		long time=micros();
		long timecomp=time+_timeFeedback;
		
		Serial.println(mess);
		while((byte)Serial.read()!=_Feedback){
			if(micros()>timecomp){
				timecomp+=_timeFeedback;
				Serial.println(mess);
			}
		}
	}else{
		Serial.println(mess);
	}
}

String SerialCom::getString()
{
	//******************************************************************
	String blueReceive="";
	char nulo = 255;//ÿ
	int conter=0;
	char blueIn=(byte)Serial.read();
	if(blueIn==_cFirst){
		blueIn=(byte)Serial.read();
		while(blueIn!=_cLast){
			if(blueIn != nulo){
				blueReceive+=blueIn;
				conter=0;
			}
			conter++;
			blueIn=(byte)Serial.read();
			if(conter>500){return "null";}
		}
		return blueReceive;//retorn o valor
		blueReceive="";
	}else{
		return "null";
	}
	//******************************************************************
}

char SerialCom::getChar()
{
	char nulo = 255;//ÿ
	int conter=0;
	//******************************************************************
	while(1){
		char ret=(byte)Serial.read();
		if(ret!=nulo){
			return ret;
		}
		conter++;
		if(conter>500){return ' ';}
	}
	//******************************************************************
}