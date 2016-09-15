#include <StepMotor.h>
//portas dos motores
int mp_11=2;
int mp_12=3;
int mp_13=4;
int mp_14=5;

int mp_21=6;
int mp_22=7;
int mp_23=8;
int mp_24=9;

StepMotor sm(mp_11,mp_12,mp_13,mp_14,mp_21,mp_22,mp_23,mp_24);//para uso de dois motores
//StepMotor sm(mp_11,mp_12,mp_13,mp_14); //se nao for usar dois motores

void setup() {
  sm.setStep(1000);//numero de passos
  sm.setStrength(0);//valor da força do motor sendo 0 fraco e 1 forte
  sm.setVelocity(100);//porcentagem da velocidade
  sm.setDirection(0,0);//set de direcao inicial para dois motores
  //sm.setDirection(0);//para um motor
}

void loop() {
  sm.Step();
  sm.RevertDirection();
}
