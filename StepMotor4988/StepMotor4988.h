/*/
     Created by TTOExtreme in 18-05-2016
/*/

#ifndef StepMotor4988_h
#define StepMotor4988_h

#include "Arduino.h"

class StepMotor4988 {
  public:
	StepMotor4988();
    StepMotor4988(int pin_Enable, int pin_Pass, int pin_Direction);
    StepMotor4988(int pin_Enable, int pin_Pass, int pin_Direction, int pin_MS1, int pin_MS2, int pin_MS3);
    void setStep(int n_pass);
	void setPorts(int pin_Enable, int pin_Pass, int pin_Direction);
	void setPorts(int pin_Enable, int pin_Pass, int pin_Direction, int pin_MS1, int pin_MS2, int pin_MS3);
    void setDirection(int Direction);
    void setMicroStepDiv(int MSDiv);
    void setVelocity(int Velocity);
    
    void RevertDirection();
    void Step();

  private:  
	int _pin_Enable;
	int _pin_Direction;
	int _pin_Pass;
	int _pin_MS1;
	int _pin_MS2;
	int _pin_MS3;

    int _Direction=0;
    int _n_pass=1;
	int _MSDiv=0;
    int _Velocity=3;
	int _MSEnable=0;
};

#endif
