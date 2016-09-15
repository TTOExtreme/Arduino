/*/
 *   Created by TTOExtreme in 18-05-2016
/*/

#include "Arduino.h"
#include "StepMotor4988.h"

StepMotor4988::StepMotor4988(){
	_MSEnable=0;
}

StepMotor4988::StepMotor4988(int pin_Enable, int pin_Pass, int pin_Direction)
{
  pinMode(pin_Enable, OUTPUT);
  digitalWrite(pin_Enable,HIGH);
  pinMode(pin_Pass, OUTPUT);
  pinMode(pin_Direction, OUTPUT);
  
  _pin_Enable=pin_Enable;
  _pin_Pass=pin_Pass;
  _pin_Direction=pin_Direction;
  
  _MSEnable=0;
}

void StepMotor4988::setPorts(int pin_Enable, int pin_Pass, int pin_Direction)
{
  pinMode(pin_Enable, OUTPUT);
  digitalWrite(pin_Enable,HIGH);
  pinMode(pin_Pass, OUTPUT);
  pinMode(pin_Direction, OUTPUT);
  
  _pin_Enable=pin_Enable;
  _pin_Pass=pin_Pass;
  _pin_Direction=pin_Direction;
  
  _MSEnable=0;
}

StepMotor4988::StepMotor4988(int pin_Enable, int pin_Pass, int pin_Direction, int pin_MS1, int pin_MS2, int pin_MS3)
{
  pinMode(pin_Enable, OUTPUT);
  digitalWrite(pin_Enable,HIGH);
  pinMode(pin_Pass, OUTPUT);
  pinMode(pin_Direction, OUTPUT);
  
  pinMode(pin_MS1, OUTPUT);
  pinMode(pin_MS2, OUTPUT);
  pinMode(pin_MS3, OUTPUT);
  
  _pin_Enable=pin_Enable;
  _pin_Pass=pin_Pass;
  _pin_Direction=pin_Direction;
  _pin_MS1=pin_MS1;
  _pin_MS2=pin_MS2;
  _pin_MS3=pin_MS3;
  
  _MSEnable=1;
}

void StepMotor4988::setPorts(int pin_Enable, int pin_Pass, int pin_Direction, int pin_MS1, int pin_MS2, int pin_MS3)
{
  pinMode(pin_Enable, OUTPUT);
  digitalWrite(pin_Enable,HIGH);
  pinMode(pin_Pass, OUTPUT);
  pinMode(pin_Direction, OUTPUT);
  
  pinMode(pin_MS1, OUTPUT);
  pinMode(pin_MS2, OUTPUT);
  pinMode(pin_MS3, OUTPUT);
  
  _pin_Enable=pin_Enable;
  _pin_Pass=pin_Pass;
  _pin_Direction=pin_Direction;
  _pin_MS1=pin_MS1;
  _pin_MS2=pin_MS2;
  _pin_MS3=pin_MS3;
  
  _MSEnable=1;
}

void StepMotor4988::setStep(int n_pass)
{
  _n_pass=n_pass; 
}

void StepMotor4988::setDirection(int Direction)
{
  _Direction=Direction;    
}

void StepMotor4988::setVelocity(int Velocity)
{ 
	if(Velocity<1002){
		_Velocity=(1002-Velocity)*1000;
	}else{
		_Velocity=(Velocity-1000);
	}
}

void StepMotor4988::setMicroStepDiv(int MSDiv)
{ 
	_MSDiv=MSDiv;
}

void StepMotor4988::RevertDirection()
{
	if(_Direction==1){
		_Direction=0;
	}else{
		if(_Direction==0){
			_Direction=1;
		}
	}
}

void StepMotor4988::Step()
{
	if(_MSEnable==1){//set Micropasso
		if(_MSDiv==0){
			digitalWrite(_pin_MS1,LOW);
			digitalWrite(_pin_MS2,LOW);
			digitalWrite(_pin_MS3,LOW);
		}else{
			if(_MSDiv==1){
				digitalWrite(_pin_MS1,HIGH);
				digitalWrite(_pin_MS2,LOW);
				digitalWrite(_pin_MS3,LOW);
			}else{
				if(_MSDiv==2){
					digitalWrite(_pin_MS1,LOW);
					digitalWrite(_pin_MS2,HIGH);
					digitalWrite(_pin_MS3,LOW);
				}else{
					if(_MSDiv==3){
						digitalWrite(_pin_MS1,HIGH);
						digitalWrite(_pin_MS2,HIGH);
						digitalWrite(_pin_MS3,LOW);
					}else{
						if(_MSDiv==4){
							digitalWrite(_pin_MS1,HIGH);
							digitalWrite(_pin_MS2,HIGH);
							digitalWrite(_pin_MS3,HIGH);
						}
					}
				}
			}
		}
	}
	if(_Direction==0){//Set direcao
		digitalWrite(_pin_Direction,LOW);
	}else{	
		digitalWrite(_pin_Direction,HIGH);
	}
	//delay(5);
	digitalWrite(_pin_Enable,LOW);//liga o modulo controlador
	for(int i=0;i<_n_pass;i++){
		digitalWrite(_pin_Pass,HIGH);
		if(_Velocity<1000){
			delayMicroseconds(_Velocity);
		}else{
			delay(_Velocity/1000);
		}
		digitalWrite(_pin_Pass,LOW);
		if(_Velocity<1000){
			delayMicroseconds(_Velocity);
		}else{
			delay(_Velocity/1000);
		}
	}
	digitalWrite(_pin_Enable,HIGH);
}