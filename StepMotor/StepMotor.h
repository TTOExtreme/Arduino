/*/
     Created by TTOExtreme in 29-04-2016
/*/

#ifndef StepMotor_h
#define StepMotor_h

#include "Arduino.h"

class StepMotor {
  public:
    StepMotor();
    StepMotor(int pin_11, int pin_12, int pin_13, int pin_14);
    StepMotor(int pin_11, int pin_12, int pin_13, int pin_14, int pin_21, int pin_22, int pin_23, int pin_24);
    void setPorts(int pin_11, int pin_12, int pin_13, int pin_14);
	void setPorts(int pin_11, int pin_12, int pin_13, int pin_14, int pin_21, int pin_22, int pin_23, int pin_24);
	void setStep(int n_pass);
    void setDirection(int Direction);
    void setDirection(int Direction, int Direction1);
    void setStrength(int Strength);
    void setVelocity(int Velocity);
    
    void RevertDirection();
    void Step();

  private:
    int _pin_11;
    int _pin_12;
    int _pin_13;
    int _pin_14;
	
    int _pin_21;
    int _pin_22;
    int _pin_23;
    int _pin_24;
	

    int _n_pass=1;
    int _Strength=0;
    int _Velocity=3;
	
    int _Direction_1=0;
	int _Direction_2=0;
	int _n_motors=1;
};

#endif
