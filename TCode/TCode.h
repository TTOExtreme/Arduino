/*/
     Created by TTOExtreme in 29-05-2016
/*/

#ifndef TCode_h
#define TCode_h

#include "WifiConfig.h"
#include "Arduino.h"
#include "SerialCom.h"
//#include "StepMotor.h"
#include "StepMotor4988.h"
#include "Servo.h"

class TCode {
	public:
	  TCode();
		
		void Init();
		void TSR();//return the pins of devices
		void Exec();//executes the program(put this func in "void loop")
		
		void T00();
		void T01();
		void T02();
		void T03();
		void T04();
		void T05();
		void T99();
		//set dispositivo
		void P00();//-automatico
		void P01();//-tempo ligado
		void P02();//-tempo desligado
		void P03();//-tempo de espera para ciclo
		void P04();//-repetiçoes no ciclo
		void P05();//-numero de ciclos
		//set motor de passo
		void S00();//-numero de passos por comando
		void S01();//-velocidade do motor
		void S02();//-divisao de micropasso
		void S03();//-automatico com retorno
		void S05();//-automatico
		void S06();//-tempo de espera para ciclo
		void S07();//-repetiçoes no ciclo
		void S08();//-numero de ciclos
		//set cnc
		void C00();//-numero de passos por milimetro
		void C01();//-numero de passos por polegada (WIP)
		void C02();//-numero de passos para 360 graus ()
		void C05();//-set origem na posicao atual
		void C81();//-posicao para ir (sistema relativo e n absoluto)
		
		//funçoes auxiliares
		void CT();//controle de temperatura
		void SMA();//stepmotor automatico
		void Decoder();//decodifica a string
		void reOrg();//separa os argumentos
		
		void C04();//-divisao de passos
		void C03();//-velocidade dos passos %
		
	private:
		//define the connections
		int _DPorts=14;//number of digital ports available
		int _APorts=8;//number of analogic ports available
		
		int _smNumber=4;//number of stepmotors (uses 4 ports if is a normal stepmotor or 3 ports if is the 4988 StepMotor)
		int _dvNumber=1;//number of devices (uses one port to control)
		int _rtNumber=1;//number of return devices (temperature sensors that retuns 0-1023 value)
		int _tpNumber=1;//number of temperature sensors
		int _dvServo=0;//number of servo motors
		
		//CNC config
		//***********************************************************
		int _CNCType=0;
		//type 0 - cartesian
		//type 1 - polar
		
		
		//type polar
		/*
		
		   //===========\\
		   ||    Seg1   ||  
		   ||           \\=========||
		   ||                Seg2  
		   ||                       
		   ||
		////\\\\\
		
		*/
		//**//
		int _CNCSeg1=334;//comprimento da primeira barra//334,257
		int _CNCSeg2=200;//comprimento da segunda barra//200
		int _CNCSeg3=405;//altura da ponta ate a mesa//405
		//**//
		
		//***********************************************************
		
		//comunication
		//***********************************************************
		int _mode=0; //0 = bluetooth; 1 = wifi;
		//Bluetooth/////////////////////////////////////////////////
		//String _password="123456";
		int _baudRate=9600;
		char _first='#';//first char of receptor
		char _last=';';//final char of receptor
		SerialCom Com=SerialCom(_baudRate, _first, _last);
		
		//WiFi/////////////////////////////////////////////////////
		WifiConfig wc = WifiConfig();
		String _comHtml="";
		//***********************************************************
		
		//stepmotors
		//***********************************************************
		int _smPins[5]{2,3,4,5,6};//pins of servomotors
			// default: {2,3,4,5,6}
			//2 - step port
			//3 - direction port
			//4 - microstep 1
			//5 - microstep 2
			//6 - microstep 3
		int _smDefault[4]{200,0,1000,0};
			// default: {1,0,100,0}
			//1 - number of steps 
			//0 - division of microstep 0-4 (0,2,4,8,16)
			//1000 - velocity 0-1000
			//0 - inicial direction
		StepMotor4988* Asm;
		//***********************************************************
		Servo* Serv;
		int* _dvPins;//pins of devices
		int* _rtPins;//pins of return devices
		String _orgCode[20];
		String _string[20];
		bool debug = false;
		
		int* _TempAuto;
		int* _TpPins;
		int* _SPins;
		int* _dvAuto;
		
		int* _smAuto;
		int* _smCRep;
		int* _smCTime;
		int* _smCNumber;
		int* _smARet;
		long*_smATimerRef;
		
		int* _dvTOn;
		int* _dvTOff;
		int* _dvCTime;
		int* _dvCRep;
		int* _dvCNumber;
		
		double _LX=0;//last x
		double _LY=0;//last y
		double _LZ=0;//last z
		
		double _PassM=0.001;//milimetros por passo
		
		int _NPassRev;//numero de passos para volta completa
		
};

#endif