#include <StepMotor4988.h>
int portEnable=45;//porta para habilitar o modulo
int portPass=44;//porta para o pulso dos passos
int portDirection=43;//porta para mudar a direção de rotação

int portMS1=51;//portas para o micropasso
int portMS2=52;
int portMS3=53;

StepMotor4988 sm(portEnable,portPass,portDirection,portMS1,portMS2,portMS3);//para uso do MicroStep
//StepMotor4988 sm(portEnable,portPass,portDirection); //se nao for usar o MicroStep

void setup() {
  sm.setStep(1000);//numero de passos
  sm.setMicroStepDiv(0);//valor de divisao de passos 0-4 sendo 0,2,4,8,16
  sm.setVelocity(100);//porcentagem da velocidade
  sm.setDirection(0);//set de direcao inicial
}

void loop() {
  sm.Step();
  sm.RevertDirection();
}