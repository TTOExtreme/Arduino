/*/
 *   Created by TTOExtreme in 18-05-2016
/*/

#include "Arduino.h"
#include "BluetoothHC06.h"

BluetoothHC06::BluetoothHC06(int PortSerial,int BaudRate)
{
	_PortSerial=PortSerial;
	_BaudRate=BaudRate;
	_hasFeedback=0;
	_hasString=0;
	
	if(_PortSerial==0){
		Serial.begin(_BaudRate);
	}else{
		if(_PortSerial==1){
			Serial1.begin(_BaudRate);
		}else{
			if(_PortSerial==2){
				Serial2.begin(_BaudRate);
			}else{
				if(_PortSerial==3){
					Serial3.begin(_BaudRate);
				}
			}
		}
	}
}
BluetoothHC06::BluetoothHC06(int PortSerial,int BaudRate, char cFirst, char cLast)
{
	_PortSerial=PortSerial;
	_BaudRate=BaudRate;
	_cFirst=cFirst;
	_cLast=cLast;
	_hasFeedback=0;
	_hasString=1;
	
	if(_PortSerial==0){
		Serial.begin(_BaudRate);
	}else{
		if(_PortSerial==1){
			Serial1.begin(_BaudRate);
		}else{
			if(_PortSerial==2){
				Serial2.begin(_BaudRate);
			}else{
				if(_PortSerial==3){
					Serial3.begin(_BaudRate);
				}
			}
		}
	}
}

void BluetoothHC06::setTimeFeedback(int timeFeedback)
{
	_timeFeedback=timeFeedback;
}

void BluetoothHC06::setFeedback(char Feedback)
{
	_Feedback=Feedback;
	_hasFeedback=1;
}

void BluetoothHC06::Send(String mess)
{
	if(_hasFeedback==1){
		long time=micros();
		long timecomp=time+_timeFeedback;
		
		if(_PortSerial==0){
			Serial.println(mess);
			while((byte)Serial.read()!=_Feedback){
				if(micros()>timecomp){
					timecomp+=_timeFeedback;
					Serial.println(mess);
				}
			}
		}else{
			if(_PortSerial==1){
				Serial1.println(mess);
				while((byte)Serial1.read()!=_Feedback){
					if(micros()>timecomp){
						timecomp+=_timeFeedback;
						Serial1.println(mess);
					}
				}
			}else{
				if(_PortSerial==2){
					Serial2.println(mess);
					while((byte)Serial2.read()!=_Feedback){
						if(micros()>timecomp){
							timecomp+=_timeFeedback;
							Serial2.println(mess);
						}
					}
				}else{
					if(_PortSerial==3){
						Serial3.println(mess);
						while((byte)Serial3.read()!=_Feedback){
							if(micros()>timecomp){
								timecomp+=_timeFeedback;
								Serial3.println(mess);
							}
						}
					}
				}
			}
		}
	}else{
		if(_PortSerial==0){
			Serial.println(mess);
		}else{
			if(_PortSerial==1){
				Serial1.println(mess);
			}else{
				if(_PortSerial==2){
					Serial2.println(mess);
				}else{
					if(_PortSerial==3){
						Serial3.println(mess);
					}
				}
			}
		}
	}
}

String BluetoothHC06::getString()
{
	if(_PortSerial==0){
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
	}else{
		if(_PortSerial==1){
		//******************************************************************
		String blueReceive="";
		char nulo = 255;//ÿ
		int conter=0;
		char blueIn=(byte)Serial1.read();
		if(blueIn==_cFirst){
			blueIn=(byte)Serial1.read();
			while(blueIn!=_cLast){
				if(blueIn != nulo){
					blueReceive+=blueIn;
					conter=0;
				}
				conter++;
				blueIn=(byte)Serial1.read();
				if(conter>500){return "null";}
			}
			return blueReceive;//retorn o valor
			blueReceive="";
		}else{
			return "null";
		}
		//******************************************************************
		}else{
			if(_PortSerial==2){
		//******************************************************************
		String blueReceive="";
		char nulo = 255;//ÿ
		int conter=0;
		char blueIn=(byte)Serial2.read();
		if(blueIn==_cFirst){
			blueIn=(byte)Serial2.read();
			while(blueIn!=_cLast){
				if(blueIn != nulo){
					blueReceive+=blueIn;
					conter=0;
				}
				conter++;
				blueIn=(byte)Serial2.read();
				if(conter>500){return "null";}
			}
			return blueReceive;//retorn o valor
			blueReceive="";
		}else{
			return "null";
		}
		//******************************************************************
			}else{
				if(_PortSerial==3){
		//******************************************************************
		String blueReceive="";
		char nulo = 255;//ÿ
		int conter=0;
		char blueIn=(byte)Serial3.read();
		if(blueIn==_cFirst){
			blueIn=(byte)Serial3.read();
			while(blueIn!=_cLast){
				if(blueIn != nulo){
					blueReceive+=blueIn;
					conter=0;
				}
				conter++;
				blueIn=(byte)Serial3.read();
				if(conter>500){return "null";}
			}
			return blueReceive;//retorn o valor
			blueReceive="";
		}else{
			return "null";
		}
		//******************************************************************
				}
			}
		}
	}
}

char BluetoothHC06::getChar()
{
	char nulo = 255;//ÿ
	int conter=0;
	if(_PortSerial==0){
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
	}else{
		if(_PortSerial==1){
		//******************************************************************
		while(1){
			char ret=(byte)Serial1.read();
			if(ret!=nulo){
				return ret;
			}
			conter++;
			if(conter>500){return ' ';}
		}
		//******************************************************************
		}else{
			if(_PortSerial==2){
		//******************************************************************
		while(1){
			char ret=(byte)Serial2.read();
			if(ret!=nulo){
				return ret;
			}
			conter++;
			if(conter>500){return ' ';}
		}
		//******************************************************************
			}else{
				if(_PortSerial==3){
		//******************************************************************
		while(1){
			char ret=(byte)Serial3.read();
			if(ret!=nulo){
				return ret;
			}
			conter++;
			if(conter>500){return ' ';}
		}
		//******************************************************************
				}
			}
		}
	}
}