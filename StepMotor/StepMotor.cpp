/*/
 *   Created by TTOExtreme in 29-04-2016
/*/

#include "Arduino.h"
#include "StepMotor.h"

StepMotor::StepMotor()
{
  int _n_pass=1;
  int _Strength=0;
  int _Velocity=3;
	
  int _Direction_1=0;
  int _Direction_2=0;
  int _n_motors=1;
}

StepMotor::StepMotor(int pin_11, int pin_12, int pin_13, int pin_14)
{
  pinMode(pin_11, OUTPUT);
  pinMode(pin_12, OUTPUT);
  pinMode(pin_13, OUTPUT);
  pinMode(pin_14, OUTPUT);
  
  digitalWrite(pin_11,LOW);
  digitalWrite(pin_12,LOW);
  digitalWrite(pin_13,LOW);
  digitalWrite(pin_14,LOW);
  
  _pin_11=pin_11;
  _pin_12=pin_12;
  _pin_13=pin_13;
  _pin_14=pin_14;
  
  _n_motors=1;
}

void StepMotor::setPorts(int pin_11, int pin_12, int pin_13, int pin_14)
{
  pinMode(pin_11, OUTPUT);
  pinMode(pin_12, OUTPUT);
  pinMode(pin_13, OUTPUT);
  pinMode(pin_14, OUTPUT);
  
  digitalWrite(pin_11,LOW);
  digitalWrite(pin_12,LOW);
  digitalWrite(pin_13,LOW);
  digitalWrite(pin_14,LOW);
  
  _pin_11=pin_11;
  _pin_12=pin_12;
  _pin_13=pin_13;
  _pin_14=pin_14;
  
  _n_motors=1;
}

StepMotor::StepMotor(int pin_11, int pin_12, int pin_13, int pin_14, int pin_21, int pin_22, int pin_23, int pin_24){
  pinMode(pin_11, OUTPUT);
  pinMode(pin_12, OUTPUT);
  pinMode(pin_13, OUTPUT);
  pinMode(pin_14, OUTPUT);
  
  pinMode(pin_21, OUTPUT);
  pinMode(pin_22, OUTPUT);
  pinMode(pin_23, OUTPUT);
  pinMode(pin_24, OUTPUT);
  
  digitalWrite(pin_21,LOW);
  digitalWrite(pin_22,LOW);
  digitalWrite(pin_23,LOW);
  digitalWrite(pin_24,LOW);
  
  digitalWrite(pin_11,LOW);
  digitalWrite(pin_12,LOW);
  digitalWrite(pin_13,LOW);
  digitalWrite(pin_14,LOW);
  
  _pin_11=pin_11;
  _pin_12=pin_12;
  _pin_13=pin_13;
  _pin_14=pin_14;
  
  _pin_21=pin_21;
  _pin_22=pin_22;
  _pin_23=pin_23;
  _pin_24=pin_24;
  
  _n_motors=2;
}

void StepMotor::setPorts(int pin_11, int pin_12, int pin_13, int pin_14, int pin_21, int pin_22, int pin_23, int pin_24){
  pinMode(pin_11, OUTPUT);
  pinMode(pin_12, OUTPUT);
  pinMode(pin_13, OUTPUT);
  pinMode(pin_14, OUTPUT);
  
  pinMode(pin_21, OUTPUT);
  pinMode(pin_22, OUTPUT);
  pinMode(pin_23, OUTPUT);
  pinMode(pin_24, OUTPUT);
  
  digitalWrite(pin_21,LOW);
  digitalWrite(pin_22,LOW);
  digitalWrite(pin_23,LOW);
  digitalWrite(pin_24,LOW);
  
  digitalWrite(pin_11,LOW);
  digitalWrite(pin_12,LOW);
  digitalWrite(pin_13,LOW);
  digitalWrite(pin_14,LOW);
  
  _pin_11=pin_11;
  _pin_12=pin_12;
  _pin_13=pin_13;
  _pin_14=pin_14;
  
  _pin_21=pin_21;
  _pin_22=pin_22;
  _pin_23=pin_23;
  _pin_24=pin_24;
  
  _n_motors=2;
}

void StepMotor::setStep(int n_pass)
{
  _n_pass=n_pass; 
}

void StepMotor::setDirection(int Direction_1)
{
  _Direction_1=Direction_1;    
}

void StepMotor::setDirection(int Direction_1, int Direction_2)
{
  _Direction_1=Direction_1;    
  _Direction_2=Direction_2;
}

void StepMotor::setStrength(int Strength)
{
  _Strength=Strength; //strength of Motor from 0 to 1
}

void StepMotor::setVelocity(int Velocity)
{ 
	_Velocity=(103-Velocity);
}

void StepMotor::RevertDirection()
{
	if(_n_motors==1){
		if(_Direction_1==1){
			_Direction_1==0;
		}else{
			if(_Direction_1==0){
				_Direction_1==1;
			}
		}
	}else{
		if(_n_motors==2){
			if(_Direction_1==1){
				_Direction_1==0;
			}else{
				if(_Direction_1==0){
					_Direction_1==1;
				}
			}
			if(_Direction_2==1){
				_Direction_2==0;
			}else{
				if(_Direction_2==0){
					_Direction_2==1;
				}
			}
		}
	}
}

void StepMotor::Step()
{
	if(_n_motors==1){
		if(_Strength==0){
			for(int i=0;i<_n_pass;i++){
				if(_Direction_1==0){
					digitalWrite(_pin_11, HIGH);
				}else{
					digitalWrite(_pin_14, HIGH);
				}
				delay(_Velocity);
				if(_Direction_1==0){
					digitalWrite(_pin_11, LOW);
					digitalWrite(_pin_12, HIGH);
				}else{
					digitalWrite(_pin_13, HIGH);
					digitalWrite(_pin_14, LOW);
				}
				delay(_Velocity);
				if(_Direction_1==0){
					digitalWrite(_pin_12, LOW);
					digitalWrite(_pin_13, HIGH);
				}else{
					digitalWrite(_pin_12, HIGH);
					digitalWrite(_pin_13, LOW);
				}
				delay(_Velocity);
				if(_Direction_1==0){
					digitalWrite(_pin_13, LOW);
					digitalWrite(_pin_14, HIGH);
				}else{
					digitalWrite(_pin_11, HIGH);
					digitalWrite(_pin_12, LOW);
				}
				delay(_Velocity);
				if(_Direction_1==0){
					digitalWrite(_pin_14, LOW);
				}else{
					digitalWrite(_pin_11,LOW);
				}
			}
			
		}else{
			if(_Strength==1){
				for(int i=0;i<_n_pass;i++){
					if(_Direction_1==0){
						digitalWrite(_pin_11, HIGH);
						digitalWrite(_pin_14, HIGH);
					}else{
						digitalWrite(_pin_14, HIGH);
						digitalWrite(_pin_11, HIGH);
					}
					delay(_Velocity);
					if(_Direction_1==0){
						digitalWrite(_pin_14, LOW);
						digitalWrite(_pin_12, HIGH);
					}else{
						digitalWrite(_pin_13, HIGH);
						digitalWrite(_pin_11, LOW);
					}
					delay(_Velocity);
					if(_Direction_1==0){
						digitalWrite(_pin_11, LOW);
						digitalWrite(_pin_13, HIGH);
					}else{
						digitalWrite(_pin_12, HIGH);
						digitalWrite(_pin_14, LOW);
					}
					delay(_Velocity);
					if(_Direction_1==0){
						digitalWrite(_pin_12, LOW);
						digitalWrite(_pin_14, HIGH);
					}else{
						digitalWrite(_pin_11, HIGH);
						digitalWrite(_pin_13, LOW);
					}
					delay(_Velocity);
					if(_Direction_1==0){
						digitalWrite(_pin_13, LOW);
						digitalWrite(_pin_11, HIGH);
					}else{
						digitalWrite(_pin_12,LOW);
						digitalWrite(_pin_14,HIGH);
					}
					delay(_Velocity);
					if(_Direction_1==0){
						digitalWrite(_pin_14, LOW);
						digitalWrite(_pin_11, LOW);
					}else{
						digitalWrite(_pin_11,LOW);
						digitalWrite(_pin_14,LOW);
					}
				}
			}
		}  
	}else{
		if(_n_motors==2){
			if(_Strength==0){
				for(int i=0;i<_n_pass;i++){
					if(_Direction_1==0){
						digitalWrite(_pin_11, HIGH);
					}else{
						digitalWrite(_pin_14, HIGH);
					}
					if(_Direction_1==0){
						digitalWrite(_pin_21, HIGH);
					}else{
						digitalWrite(_pin_24, HIGH);
					}
					delay(_Velocity);
					if(_Direction_1==0){
						digitalWrite(_pin_11, LOW);
						digitalWrite(_pin_12, HIGH);
					}else{
						digitalWrite(_pin_13, HIGH);
						digitalWrite(_pin_14, LOW);
					}
					if(_Direction_2==0){
						digitalWrite(_pin_21, LOW);
						digitalWrite(_pin_22, HIGH);
					}else{
						digitalWrite(_pin_23, HIGH);
						digitalWrite(_pin_24, LOW);
					}
					delay(_Velocity);
					if(_Direction_1==0){
						digitalWrite(_pin_12, LOW);
						digitalWrite(_pin_13, HIGH);
					}else{
						digitalWrite(_pin_12, HIGH);
						digitalWrite(_pin_13, LOW);
					}
					if(_Direction_2==0){
						digitalWrite(_pin_22, LOW);
						digitalWrite(_pin_23, HIGH);
					}else{
						digitalWrite(_pin_22, HIGH);
						digitalWrite(_pin_23, LOW);
					}
					delay(_Velocity);
					if(_Direction_1==0){
						digitalWrite(_pin_13, LOW);
						digitalWrite(_pin_14, HIGH);
					}else{
						digitalWrite(_pin_11, HIGH);
						digitalWrite(_pin_12, LOW);
					}
					if(_Direction_2==0){
						digitalWrite(_pin_23, LOW);
						digitalWrite(_pin_24, HIGH);
					}else{
						digitalWrite(_pin_21, HIGH);
						digitalWrite(_pin_22, LOW);
					}
					delay(_Velocity);
					if(_Direction_1==0){
						digitalWrite(_pin_14, LOW);
					}else{
						digitalWrite(_pin_11, LOW);
					}
					if(_Direction_2==0){
						digitalWrite(_pin_24, LOW);
					}else{
						digitalWrite(_pin_21, LOW);
					}
				}
			}else{
				if(_Strength==1){
					for(int i=0;i<_n_pass;i++){
						if(_Direction_1==0){
							digitalWrite(_pin_11, HIGH);
							digitalWrite(_pin_14, HIGH);
						}else{
							digitalWrite(_pin_14, HIGH);
							digitalWrite(_pin_11, HIGH);
						}
						if(_Direction_2==0){
							digitalWrite(_pin_21, HIGH);
							digitalWrite(_pin_24, HIGH);
						}else{
							digitalWrite(_pin_24, HIGH);
							digitalWrite(_pin_21, HIGH);
						}
						delay(_Velocity);
						if(_Direction_1==0){
							digitalWrite(_pin_14, LOW);
							digitalWrite(_pin_12, HIGH);
						}else{
							digitalWrite(_pin_13, HIGH);
							digitalWrite(_pin_11, LOW);
						}
						if(_Direction_2==0){
							digitalWrite(_pin_24, LOW);
							digitalWrite(_pin_22, HIGH);
						}else{
							digitalWrite(_pin_23, HIGH);
							digitalWrite(_pin_21, LOW);
						}
						delay(_Velocity);
						if(_Direction_1==0){
							digitalWrite(_pin_11, LOW);
							digitalWrite(_pin_13, HIGH);
						}else{
							digitalWrite(_pin_12, HIGH);
							digitalWrite(_pin_14, LOW);
						}
						if(_Direction_2==0){
							digitalWrite(_pin_21, LOW);
							digitalWrite(_pin_23, HIGH);
						}else{
							digitalWrite(_pin_22, HIGH);
							digitalWrite(_pin_24, LOW);
						}
						delay(_Velocity);
						if(_Direction_1==0){
							digitalWrite(_pin_12, LOW);
							digitalWrite(_pin_14, HIGH);
						}else{
							digitalWrite(_pin_11, HIGH);
							digitalWrite(_pin_13, LOW);
						}
						if(_Direction_2==0){
							digitalWrite(_pin_22, LOW);
							digitalWrite(_pin_24, HIGH);
						}else{
							digitalWrite(_pin_21, HIGH);
							digitalWrite(_pin_23, LOW);
						}/*
						delay(_Velocity);
						if(_Direction_1==0){
							digitalWrite(_pin_13, LOW);
							digitalWrite(_pin_11, HIGH);
						}else{
							digitalWrite(_pin_12,LOW);
							digitalWrite(_pin_14,HIGH);
						}
						if(_Direction_2==0){
							digitalWrite(_pin_23, LOW);
							digitalWrite(_pin_21, HIGH);
						}else{
							digitalWrite(_pin_22,LOW);
							digitalWrite(_pin_24,HIGH);
						}*/
						delay(_Velocity);
						if(_Direction_1==0){
							digitalWrite(_pin_14, LOW);
							digitalWrite(_pin_13, LOW);
						}else{
							digitalWrite(_pin_11,LOW);
							digitalWrite(_pin_12,LOW);
						}
						if(_Direction_2==0){
							digitalWrite(_pin_24, LOW);
							digitalWrite(_pin_23, LOW);
						}else{
							digitalWrite(_pin_21,LOW);
							digitalWrite(_pin_22,LOW);
						}
					}
				}
			}  
		}
	}
}

