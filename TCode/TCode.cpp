/*/
 *   Created by TTOExtreme in 29-05-2016
/*/

#include "Arduino.h"
#include "TCode.h"
#include "SerialCom.h"
#include <Servo.h>
#include "WifiConfig.h"
//#include "StepMotor4988.h"

TCode::TCode(String mode){
	if(mode=="Bluetooth"){_mode=0;}
	if(mode=="WiFi"){_mode=1;}
	if(debug){Com.Send("declarated");}
}

void TCode::Init(){
	if(_mode==1){wc.Init();}
	int lastPort=0;
	int lastAPort=0;
	//if(debug){Com.Send("Init");}
	
	if(_smNumber>0){
		delete [] Asm;
		delete [] _smAuto;
		delete [] _smCRep;
		delete [] _smCTime;
		delete [] _smCNumber;
		delete [] _smATimerRef;
		delete [] _smARet;
		
		Asm=new StepMotor4988[_smNumber];
		_smAuto=new int[_smNumber];
		_smCRep=new int[_smNumber];
		_smCTime=new int[_smNumber];
		_smCNumber=new int[_smNumber];
		_smATimerRef=new long[_smNumber];
		_smARet=new int[_smNumber];
		
		for(int i=0;i<_smNumber;i++){
			Asm[i].setPorts(i+5+_smPins[0],_smPins[0],_smPins[1],_smPins[2],_smPins[3],_smPins[4]);
			//2 - step port
			//3 - direction port
			//4 - microstep 1
			//5 - microstep 2
			//6 - microstep 3
			
			Asm[i].setStep(_smDefault[0]);
			Asm[i].setMicroStepDiv(_smDefault[1]);
			Asm[i].setVelocity(_smDefault[2]);
			Asm[i].setDirection(_smDefault[3]);
			
			_smAuto[i]=0;
			_smCRep[i]=2;
			_smCTime[i]=100;
			_smCNumber[i]=2;
			_smARet[i]=1;
			
			lastPort=i+6+_smPins[0];
		}
	}
	if(_dvNumber>0){
		delete [] _dvPins;
		delete [] _dvAuto;
		delete [] _dvTOn;
		delete [] _dvTOff;
		delete [] _dvCTime;
		delete [] _dvCRep;
		delete [] _dvCNumber;
		
		_dvPins=new int[_dvNumber];
		_dvAuto=new int[_dvNumber];
		_dvTOn=new int[_dvNumber];
		_dvTOff=new int[_dvNumber];
		_dvCTime=new int[_dvNumber];
		_dvCRep=new int[_dvNumber];
		_dvCNumber=new int[_dvNumber];
		
		for(int i=0;i<_dvNumber;i++){
			_dvPins[i]=i+lastPort+1;
			_dvAuto[i]=0;
			_dvTOn[i]=0;
			_dvTOff[i]=0;
			_dvCTime[i]=0;
			_dvCRep[i]=0;
			_dvCNumber[i]=0;
		}
		lastPort+=_dvNumber;
	}
	if(_rtNumber>0){
		for(int i=0;i<_rtNumber;i++){
			_rtPins[i]=i+lastPort;
		}
		lastAPort+=_rtNumber; 
	}
	if(_tpNumber>0){
		delete [] _TempAuto;
		delete [] _TpPins;
		
		_TempAuto=new int[_tpNumber];
		_TpPins=new int[_tpNumber];
		
		for(int i=0;i<_tpNumber;i++){
			_TempAuto[i]=0;
			_TpPins[i]=lastAPort+i;
		}
		lastAPort+=_tpNumber;
	}
	if(_dvServo>0){
		delete[] Serv;
		delete[] _SPins;
		Serv = new Servo[_dvServo];
		_SPins = new int[_dvServo];
		
		for(int i=0;i<_dvServo;i++){
			Serv[i].attach(lastPort+i);
			_SPins[i]=lastPort+i;
		}
		
		lastPort+=_dvServo;
	}
	//if(debug){TSR();}
}

void TCode::TSR(){
	if(_smNumber>0){
		if(_mode=0){
			Com.Send("========================");
			Com.Send("StepMotors ports:");
			Com.Send("   step port: "+String(_smPins[0]));
			Com.Send("   direction port: "+String(_smPins[1]));
			Com.Send("   microstep 1 port: "+String(_smPins[2]));
			Com.Send("   microstep 2 port: "+String(_smPins[3]));
			Com.Send("   microstep 3 port: "+String(_smPins[4]));
			Com.Send("   enable ports: "+String(_smNumber+6));
			Com.Send("========================");
		}else{
			_comHtml="";//reset the com site
			
			_comHtml += "<pre>========================</pre>";
			_comHtml += "<pre>StepMotors ports:</pre>";
			_comHtml += "<pre>   step port: "+String(_smPins[0])+"</pre>";
			_comHtml += "<pre>   direction port: "+String(_smPins[1])+"</pre>";
			_comHtml += "<pre>   microstep 1 port: "+String(_smPins[2])+"</pre>";
			_comHtml += "<pre>   microstep 2 port: "+String(_smPins[3])+"</pre>";
			_comHtml += "<pre>   microstep 3 port: "+String(_smPins[4])+"</pre>";
			_comHtml += "<pre>   enable ports: "+String(_smNumber+6)+"</pre>";
			_comHtml += "<pre>========================</pre>";
		}
	}
	if(_dvNumber>0){
		if(_mode==0){
			Com.Send("========================");
			Com.Send("Devices ports:");
			for(int i=0;i<_dvNumber;i++){
				Com.Send("Device: "+String(i+1)+" Port: "+String(_dvPins[i]));
			}
			Com.Send("========================");
		}else{
			_comHtml += "<pre>========================</pre>";
			_comHtml += "<pre>Devices ports:</pre>";
			for(int i=0;i<_dvNumber;i++){
				_comHtml += "<pre>Device: "+String(i+1)+" Port: "+String(_dvPins[i])+"</pre>";
			}
			_comHtml += "========================";
		}
	}
	if(_rtNumber>0){
		if(_mode==0){
			Com.Send("========================");
			Com.Send("Return ports:");
			for(int i=0;i<_rtNumber;i++){
				Com.Send("Device: "+String(i+1)+" Port: A"+String(_rtPins[i]));
			}
			Com.Send("========================");
		}else{
			_comHtml += "<pre>========================</pre>";
			_comHtml += "<pre>Return ports:</pre>";
			for(int i=0;i<_rtNumber;i++){
				_comHtml += "<pre>Device: "+String(i+1)+" Port: A"+String(_rtPins[i])+"</pre>";
			}
			_comHtml += "<pre>========================</pre>";
		}
	}
	if(_tpNumber>0){
		if(_mode==0){
			Com.Send("========================");
			Com.Send("Temperature sensors:");
			for(int i=0;i<_tpNumber;i++){
				Com.Send("Sensor: "+String(i+1)+" Port: A"+String(_TpPins[i])+" Control (Output):"+String(_dvPins[i]));
			}
			Com.Send("========================");
		}else{
			_comHtml += "<pre>========================</pre>";
			_comHtml += "<pre>Temperature sensors:</pre>";
			for(int i=0;i<_tpNumber;i++){
				_comHtml += "<pre>Sensor: "+String(i+1)+" Port: A"+String(_TpPins[i])+" Control (Output):"+String(_dvPins[i])+"</pre>";
			}
			_comHtml += "<pre>========================</pre>";
		}
	}
	if(_dvServo>0){
		if(_mode==0){
			Com.Send("========================");
			Com.Send("Servo motors:");
			for(int i=0;i<_dvServo;i++){
				Com.Send("Device: "+String(i+1)+" Port: "+String(_SPins[i]));
			}
			Com.Send("========================");
		}else{
			_comHtml += "<pre>========================</pre>";
			_comHtml += "<pre>Servo motors:</pre>";
			for(int i=0;i<_dvServo;i++){
				_comHtml += "<pre>Device: "+String(i+1)+" Port: "+String(_SPins[i])+"</pre>";
			}
			_comHtml += "<pre>========================</pre>";
		}
	}
}

void TCode::Exec(){
	if(_mode==1){wc.Exec();}
	_string[0]="";
	Decoder();
	SMA();
	CT();
	//_orgCode[20]="";
	if(_string[0]=="TSR"){//#TSR;
		TSR();
		if(_mode==0){Com.Send("N");}else{_comHtml+="<pre>n</pre>"}
	}
	if(_string[0]=="T00"){//#T00;
		T00();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="T01"){//#T01 Dv01 St01;
		T01();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="T02"){//#T02 Dv01 RtH Ps200;
		T02();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="T03"){//#T03 Dv00 Ps20;
		T03();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="T04"){//#T04 Dv00;
		T04();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="T05"){//#T05 Dv00 Tp500;  (Tp need to converts temp to 0-1023) Dv is the corespondent Aport
		T05();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="T99"){//#T99;
		T99();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="P00"){//#P00 Dv00 St1; St1=automatico on St0=off
		P00();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="P01"){//#P01 Dv00 Tp1000;-tempo ligado
		P01();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="P02"){//#P02 Dv00 Tp1000;-tempo desligado
		P02();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="P03"){//#P03 Dv00 Tp1000;-tempo de espera para ciclo
		P03();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="P04"){//#P04 Dv00 Rt100;-repetiçoes no ciclo
		P04();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="P05"){//#P05 Dv00 Ps100;-numero de ciclos
		P05();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="S00"){//#S00 Dv00 Ps100; -numero de passos por comando (A)
		S00();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="S01"){//#S01 Dv00 Tp100;- % velocidade do motor (M/A)
		S01();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="S02"){//#S02 Dv00 Ms4;-divisao de micropasso (M/A) 0-4 >> 0-16 divisoes
		S02();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="S03"){//#S03 Dv00 Rt1;-automatico com retorno (A)
		S03();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="S05"){//#S05 Dv00 St0;-automatico (A)
		S05();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="S06"){//#S06 Dv00 Tp1000;-tempo de espera para ciclo (A)
		S06();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="S07"){//#S07 Dv00 Rt100;-repetiçoes no ciclo (A)
		S07();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="S08"){//#S08 Dv00 Ps50;-numero de ciclos (A)
		S08();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="C00"){//#C00 Ps50;-numero de passos por decimo de milimetro
		C00();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="C01"){//#C01 Ps50;-numero de passos por polegada (W.I.P.)
		C01();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="C02"){//#C02 Ps50;-numero de passos para 360 graus
		C02();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="C03"){//#C03 Tp50;-velocidade dos passos %
		C03();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="C04"){//#C04 Ps50;-divisao de passos
		C04();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_string[0]=="C81"||_string[0]=="G1"){//#C81 X10 Y20 Z20;-posicao para ir (absoluto)
		C81();
		if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	}
	if(_mode==1){ wc.SetComSite(_comHtml); }
}

void TCode::T00(){//retorna estado de conexao 
	if(_mode==0){Com.Send("y");}else{_comHtml="<pre>y</pre>"}
}

void TCode::T01(){//controle de dispositivo 
	reOrg();
	if(_orgCode[1]=="00"){
		digitalWrite(_dvPins[_orgCode[0].toInt()],LOW);
	}else{
		digitalWrite(_dvPins[_orgCode[0].toInt()],HIGH);
	}
}

void TCode::T02(){//controle motor de passo
	reOrg();
	Asm[_orgCode[0].toInt()].setStep(_orgCode[4].toInt());
	//Asm[_orgCode[0].toInt()].setMicroStepDiv(_orgCode[3].toInt());
	//Asm[_orgCode[0].toInt()].setVelocity(_orgCode[5].toInt());
	Asm[_orgCode[0].toInt()].setDirection(_orgCode[2].toInt());
	Asm[_orgCode[0].toInt()].Step();
}

void TCode::T03(){//controle do servo
	reOrg();
	Serv[_orgCode[0].toInt()].write(_orgCode[4].toInt());
}

void TCode::T04(){//retorno de dados da porta
	reOrg();
	if(_mode==0){Com.Send("N");}else{_comHtml="<pre>n</pre>"}
	Com.Send(String(analogRead(_rtPins[_orgCode[0].toInt()])));
}

void TCode::T05(){
	reOrg();
	_TempAuto[_orgCode[0].toInt()]=_orgCode[5].toInt();
}

void TCode::T99(){//parada de emergencia
	while(1){Com.Send("Emergency");}
}

void TCode::P00(){
	reOrg();
	_dvAuto[_orgCode[0].toInt()]=_orgCode[1].toInt();
}

void TCode::P01(){
	reOrg();
	_dvTOn[_orgCode[0].toInt()]=_orgCode[5].toInt();
}

void TCode::P02(){
	reOrg();
	_dvTOff[_orgCode[0].toInt()]=_orgCode[5].toInt();
}

void TCode::P03(){
	reOrg();
	_dvCTime[_orgCode[0].toInt()]=_orgCode[5].toInt();
}

void TCode::P04(){
	reOrg();
	_dvCRep[_orgCode[0].toInt()]=_orgCode[2].toInt();
}

void TCode::P05(){
	reOrg();
	_dvCNumber[_orgCode[0].toInt()]=_orgCode[4].toInt();
}

void TCode::S00(){
	reOrg();
	Asm[_orgCode[0].toInt()].setStep(_orgCode[4].toInt());
}

void TCode::S01(){
	reOrg();
	Asm[_orgCode[0].toInt()].setVelocity(_orgCode[5].toInt());
}

void TCode::S02(){
	reOrg();
	Asm[_orgCode[0].toInt()].setMicroStepDiv(_orgCode[3].toInt());
}

void TCode::S03(){
	reOrg();
	_smARet[_orgCode[0].toInt()]=_orgCode[2].toInt();
}

void TCode::S05(){
	reOrg();
	_smAuto[_orgCode[0].toInt()]=_orgCode[1].toInt();
	_smATimerRef[_orgCode[0].toInt()]=micros();
}

void TCode::S06(){
	reOrg();
	_smCTime[_orgCode[0].toInt()]=_orgCode[5].toInt();
}

void TCode::S07(){
	reOrg();
	_smCRep[_orgCode[0].toInt()]=_orgCode[1].toInt();
}

void TCode::S08(){
	reOrg();
	_smCNumber[_orgCode[0].toInt()]=_orgCode[4].toInt();
}

void TCode::C00(){
	reOrg();
	_PassM=_orgCode[4].toFloat();
	C04();
	Asm[0].setStep(1);
	Asm[1].setStep(1);
	Asm[2].setStep(1);
}

void TCode::C01(){
	reOrg();
	Asm[0].setStep(_orgCode[4].toInt());
	Asm[1].setStep(_orgCode[4].toInt());
	Asm[2].setStep(_orgCode[4].toInt());
}

void TCode::C02(){
	reOrg();
	_NPassRev=_orgCode[4].toInt();
}

void TCode::C05(){
	_LX=0;
	_LY=0;
	_LZ=0;
}

void TCode::C81(){
	reOrg();
	if(_orgCode[9].toInt()>0){
		C03();//muda a velocidade
	}
	double x1=_orgCode[6].toFloat();
	double y1=_orgCode[7].toFloat();
	double z1=_orgCode[8].toFloat();
	
	int xty=1;//steps of x to do an y 
	int ytx=1;//steps of y to do an x
	
	if(_CNCType==0){
		
		int passcount[3]{0,0,0};//x y z 
		int passnum[3]{0,0,0};
		
		passnum[0]=sqrt(x1-_LX).toInt();
		passnum[1]=sqrt(y1-_LY).toInt();
		passnum[2]=sqrt(z1-_LZ).toInt();
		
		int minnum=passnum[0];
		if(passnum[1]<minnum){ minnum=passnum[1]; }
		if(passnum[2]<minnum){ minnum=passnum[2]; }
		
		passcount[0]=(passnum[0]/minnum).toInt();
		passcount[1]=(passnum[1]/minnum).toInt();
		passcount[2]=(passnum[2]/minnum).toInt();
		
		for(int i=minnum;i>0;i--){
			for(int xnum=passcount[0];xnum>0;xnum-- ){
				if(x1>_LX){
					Asm[0].setDirection(1);
					Asm[0].Step();
					_LX -= 0.001;
				}else{
					if(x1<_LX){
						Asm[0].setDirection(0);
						Asm[0].Step();
						_LX += 0.001;
					}
				}
			}
			for(int ynum=passcount[1];ynum>0;ynum-- ){
				if(y1>_LY){
					Asm[1].setDirection(1);
					Asm[1].Step();
					_LY -= 0.001;
				}else{
					if(y1<_LY){
						Asm[1].setDirection(0);
						Asm[1].Step();
						_LY += 0.001;
					}
				}
			}
			for(int znum=passcount[2];znum>0;znum-- ){
				if(z1>_LZ){
					Asm[2].setDirection(1);
					Asm[2].Step();
					_LZ -= 0.001;
				}else{
					if(z1<_LZ){
						Asm[2].setDirection(0);
						Asm[2].Step();
						_LZ += 0.001;
					}
				}
			}
		}
		
		
		int sec=0;
		while(1){
			//security
			sec++;
			if(sec>20000){break;}
			//Com.Send("C81");
			
			if(xty>ytx){
				for(int i=0;i<xty;i++){
					if(x1>_LX){
						Asm[0].setDirection(1);
						Asm[0].Step();
						_LX -= 0.001;
					}else{
						if(x1<_LX){
							Asm[0].setDirection(0);
							Asm[0].Step();
							_LX += 0.001;
						}
					}
				}
				if(y1>_LY){
					Asm[1].setDirection(1);
					Asm[1].Step();
					_LY -= 0.001;
				}else{
					if(y1<_LY){
						Asm[1].setDirection(0);
						Asm[1].Step();
						_LY += 0.001;
					}
				}
			}else{
				for(int i=0;i<ytx;i++){
					if(y1>_LY){
						Asm[1].setDirection(1);
						Asm[1].Step();
						_LY -= 0.001;
					}else{
						if(y1<_LX){
							Asm[1].setDirection(0);
							Asm[1].Step();
							_LY += 0.001;
						}
					}
				}
				if(x1>_LX){
					Asm[0].setDirection(1);
					Asm[0].Step();
					_LX -= 0.001;
				}else{
					if(x1<_LX){
						Asm[0].setDirection(0);
						Asm[0].Step();
						_LX += 0.001;
					}
				}
			}
			
			//movimentation in z
			if(z1>_LZ){
				Asm[2].setDirection(1);
				Asm[2].Step();
				_LZ -= 0.001;
			}else{
				if(z1<_LZ){
					Asm[2].setDirection(0);
					Asm[2].Step();
					_LZ += 0.001;
				}
			}
			if(x1==_LX && y1==_LY && z1==_LZ){break;}
		}//*/
	}else{
		double nSQ=atan2(y1,x1);//angulo s+q
		double nQ=acos(((x1*x1)+(y1*y1)+(_CNCSeg1*_CNCSeg1)-(_CNCSeg2*_CNCSeg2))/(2*_CNCSeg1*sqrt((x1*x1)+(y1*y1))));
		double nS=nSQ-nQ;
		double nE=acos(((x1*x1)+(y1*y1)+(_CNCSeg1*_CNCSeg1)-(_CNCSeg2*_CNCSeg2))/(2*_CNCSeg1*_CNCSeg2));
		
		int _x1=(_NPassRev/360)*nS;
		int _y1=(_NPassRev/360)*nE;
		int sec=0;
		while(1){
			//Com.Send("C81 2");
			
			sec++;
			if(sec>20000){break;}
			if(_x1>_LX){
				Asm[0].setDirection(1);
				Asm[0].Step();
				_LX-= 0.001;
			}else{
				if(_x1<_LX){
					Asm[0].setDirection(0);
					Asm[0].Step();
					_LX+= 0.001;
				}
			}
			if(_y1>_LY){
				Asm[1].setDirection(1);
				Asm[1].Step();
				_LY-= 0.001;
			}else{
				if(_y1<_LY){
					Asm[1].setDirection(0);
					Asm[1].Step();
					_LY+= 0.001;
				}
			}
			if(z1>_LZ){
				Asm[2].setDirection(1);
				Asm[2].Step();
				_LZ-= 0.001;
			}else{
				if(z1<_LZ){
					Asm[2].setDirection(0);
					Asm[2].Step();
					_LZ+= 0.001;
				}
			}
			if(x1==_LX && y1==_LY && z1==_LZ){break;}
		}
	}
}

//aux func
//******************************************************************
void TCode::CT(){
	for(int i=0;i<_tpNumber;i++){
		int val=analogRead(_TpPins[i]);
		if(val<_TempAuto[i]){
			digitalWrite(_dvPins[i],HIGH);
		}else{
			digitalWrite(_dvPins[i],LOW);
		}
	}
}

void TCode::SMA(){
	for(int i=0;i<_smNumber;i++){
		if(_smAuto[i]==1){
			if(_smATimerRef[i]<micros()){
				if(_smCNumber[i]>0){
					_smATimerRef[i]+=_smCTime[i];
					for(int j=0;j<_smCRep[i];j++){
						Asm[i].Step();
						Decoder();
					}
					if(_smARet[i]==1){
						Asm[i].RevertDirection();
					}
					_smCNumber[i]--;
					_smATimerRef[i]==micros()+_smCTime[i];
				}else{
					if(_smCNumber[i]==-1){
						_smATimerRef[i]+=_smCTime[i];
						for(int j=0;j<_smCRep[i];j++){
							Asm[i].Step();
							Decoder();
						}
						if(_smARet[i]==1){
							Asm[i].RevertDirection();
						}
					}else{
						if(_smCNumber[i]==0){
							_smAuto[i]=0;
						}
					}
					_smATimerRef[i]==micros()+_smCTime[i];
				}
			}
		}
	}
			//Com.Send("end ");
}

void TCode::Decoder(){
	_string[19]="";
	String comando="";
	int pos=0;
	int fpos=0;
	int i=0;
	if(_mode==0){comando=Com.getString();}else{comando=wc.GetCommandRecieved()}
	if(comando!="null"){
		_string[19]=comando;
		//if(debug){Com.Send("Recieve: "+_string[20]);}
		fpos=comando.length();
		while(pos>-1){
			pos=comando.indexOf(" ");
			//if(debug){Com.Send("pos of string: "+String(pos));}
			if(pos==-1 && i==0){
				_string[0]=comando;
				//if(debug){Com.Send("in the if: "+_string[0]);}
			}else{
				_string[i]=comando.substring(0,pos);
				comando=comando.substring(pos+1);
				//if(debug){Com.Send("in else: "+_string[i]+" "+String(i));}
				i++;
			}
		}
	}
}

void TCode::reOrg(){	
	for(int i=2;i<20;i++){
          if(_string[i].indexOf("D")!=-1){
            _orgCode[0]=_string[i].substring(_string[i].indexOf("Dv")+2);
			//device
            //if(debug){Com.Send("_orgCode[0]="+_orgCode[0]);}
          }
          if(_string[i].indexOf("S")!=-1){
            _orgCode[1]=_string[i].substring(_string[i].indexOf("St")+2);
			//state
            //if(debug){Com.Send("_orgCode[1]="+_orgCode[1]);}
          }
          if(_string[i].indexOf("R")!=-1){
            _orgCode[2]=_string[i].substring(_string[i].indexOf("Rt")+2);
			//rotate A or H
            //if(debug){Com.Send("_orgCode[2]="+_orgCode[2]);
          }
          if(_string[i].indexOf("M")!=-1){
            _orgCode[3]=_string[i].substring(_string[i].indexOf("Ms")+2);
			//micro step
            //if(debug){Com.Send("_orgCode[3]="+_orgCode[3]);}
          }
          if(_string[i].indexOf("P")!=-1){
            _orgCode[4]=_string[i].substring(_string[i].indexOf("Ps")+2);
			//passos
            //if(debug){Com.Send("_orgCode[4]="+_orgCode[4]);}
          }
          if(_string[i].indexOf("T")!=-1){
            _orgCode[5]=_string[i].substring(_string[i].indexOf("Tp")+2);
			//Velocidade de rotacao
            //if(debug){Com.Send("_orgCode[5]="+_orgCode[5]);}
          }
          if(_string[i].indexOf("X")!=-1){
            _orgCode[6]=_string[i].substring(_string[i].indexOf("X")+1);
			//Estado do 
            //if(debug){Com.Send("_orgCode[6]="+_orgCode[6]);}
          }
          if(_string[i].indexOf("Y")!=-1){
            _orgCode[7]=_string[i].substring(_string[i].indexOf("Y")+1);
			//Delay Desligado
            //if(debug){Com.Send("_orgCode[7]="+_orgCode[7]);}
          }
          if(_string[i].indexOf("Z")!=-1){
            _orgCode[8]=_string[i].substring(_string[i].indexOf("Z")+1);//
			//delay entre repetiçoes
            //if(debug){Com.Send("_orgCode[8]="+_orgCode[8]);}
          }
          if(_string[i].indexOf("F")!=-1){
            _orgCode[9]=_string[i].substring(_string[i].indexOf("F")+1);//feedrate in mm/min
			//delay entre repetiçoes
            //if(debug){Com.Send("_orgCode[8]="+_orgCode[8]);}
          }
    }
}

void TCode::C04(){
	//reOrg();
	if(_PassM >= 0.001){
		double nv =_PassM;
		if(nv > 24){//24=16+8
			Com.Send("[Error] Precision below expected");
		}else{
			if(nv <= 24 && nv > 12){
				Asm[0].setMicroStepDiv(4);
				Asm[1].setMicroStepDiv(4);
				Asm[2].setMicroStepDiv(4);
			}else{
				if(nv <=12 && nv > 6){
					Asm[0].setMicroStepDiv(3);
					Asm[1].setMicroStepDiv(3);
					Asm[2].setMicroStepDiv(3);
				}else{
					if(nv <=6 && nv > 3){
						Asm[0].setMicroStepDiv(2);
						Asm[1].setMicroStepDiv(2);
						Asm[2].setMicroStepDiv(2);
					}else{
						if(nv <=3 && nv > 1){
							Asm[0].setMicroStepDiv(1);
							Asm[1].setMicroStepDiv(1);
							Asm[2].setMicroStepDiv(1);
						}else{
							Asm[0].setMicroStepDiv(0);
							Asm[1].setMicroStepDiv(0);
							Asm[2].setMicroStepDiv(0);
						}
					}
				}
			}
		}
	}
	/*
	Asm[0].setMicroStepDiv(_orgCode[3].toInt());
	Asm[1].setMicroStepDiv(_orgCode[3].toInt());
	Asm[2].setMicroStepDiv(_orgCode[3].toInt());
	*/
}

void TCode::C03(){
	//reOrg();
	int veloc=(_orgCode[9].toInt()/60);//tempo entre cada passo em milisegundo =veloc*1000(s > ms)/1000(mm > milesimo de mm)
	Asm[0].setVelocity(veloc);
	Asm[1].setVelocity(veloc);
	Asm[2].setVelocity(veloc);
}
