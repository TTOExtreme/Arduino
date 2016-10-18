/*/
 *   Created by TTOExtreme in 08-09-2016
/*/

#include <WifiConfig.h>
#include <Thermistor.h>

WifiConfig wc;

const byte tmpPort = A0;//temperature
const byte dorPort = D0;//door

const byte co2Port = D1;//co2
const byte o2Port = D2;//o2
const byte n2Port = D3;//n2

const byte dv1Port = D4;//dev1
const byte dv2Port = D5;//dev2
const byte dv3Port = D6;//dev3

const byte hetPort = D7;//heat
const byte fanPort = D8;//fan

const byte ligPort = D9;//light D9
const byte luvPort = D10;//light uv D10

int portOff = HIGH;
int portOn = LOW;

String co2St="Off",o2St="Off",n2St="Off", dv1St="Off",dv2St="Off",dv3St="Off", hetSt="Off",fanSt="Off", ligSt="Off",luvSt="Off";
String HeatSec="Off";

double temperature=0.0;

Thermistor temp(tmpPort);

void setup() {
  //ESP.wdtDisable();
  wc.SetIpEnd(176);
  wc.Init();
  pinMode(tmpPort,INPUT); 
  pinMode(dorPort,INPUT);
  
  pinMode(co2Port,OUTPUT); digitalWrite(co2Port,HIGH);
  pinMode(o2Port,OUTPUT); digitalWrite(o2Port,HIGH);
  pinMode(n2Port,OUTPUT); digitalWrite(n2Port,HIGH);
  
  pinMode(dv1Port,OUTPUT); digitalWrite(dv1Port,HIGH);
  pinMode(dv2Port,OUTPUT); digitalWrite(dv2Port,HIGH);
  pinMode(dv3Port,OUTPUT); digitalWrite(dv3Port,HIGH);
  
  pinMode(ligPort,OUTPUT); digitalWrite(ligPort,HIGH);
  pinMode(luvPort,OUTPUT); digitalWrite(luvPort,HIGH);
  
  pinMode(hetPort,OUTPUT); digitalWrite(hetPort,HIGH);
  pinMode(fanPort,OUTPUT); digitalWrite(fanPort,HIGH);
}

void loop() {
  changeComCode();
  //if(GetDoor()=="Open" != -1){ digitalWrite(fanPort,portOff); fanSt = "Off";}
  wc.Exec();
  //Serial.println("execute");
  PortControl(wc.GetCommandRecieved());
}

void PortControl(String com){
  if(com.indexOf("@temp=") != -1){ 
    if(com.lastIndexOf("@")>2){
      double tempera=((com.substring(com.indexOf("@temp=") + 6,com.substring(5).indexOf("@")+5)).toInt());
      temperature = tempera/10;
      //Serial.println("temperature get: " + String(temperature));
    }else{
      double tempera=((com.substring(com.indexOf("@temp=") + 6)).toInt());
      temperature = tempera/10;
      //Serial.println("temperature get: " + String(temperature));
    }
  }
  
  if(com.indexOf("@co2=On") != -1){ digitalWrite(co2Port,portOn); co2St = "On";}
  if(com.indexOf("@co2=Off") != -1){ digitalWrite(co2Port,portOff); co2St = "Off";}
  
  if(com.indexOf("@o2=On") != -1){ digitalWrite(o2Port,portOn); o2St = "On";}
  if(com.indexOf("@o2=Off") != -1){ digitalWrite(o2Port,portOff); o2St = "Off";}
  
  if(com.indexOf("@n2=On") != -1){ digitalWrite(n2Port,portOn); n2St = "On";}
  if(com.indexOf("@n2=Off") != -1){ digitalWrite(n2Port,portOff); n2St = "Off";}
  
  if(com.indexOf("@dv1=On") != -1){ digitalWrite(dv1Port,portOn); dv1St = "On";}
  if(com.indexOf("@dv1=Off") != -1){ digitalWrite(dv1Port,portOff); dv1St = "Off";}
  
  if(com.indexOf("@dv2=On") != -1){ digitalWrite(dv2Port,portOn); dv2St = "On";}
  if(com.indexOf("@dv2=Off") != -1){ digitalWrite(dv2Port,portOff); dv2St = "Off";}
  
  if(com.indexOf("@dv3=On") != -1){ digitalWrite(dv3Port,portOn); dv3St = "On";}
  if(com.indexOf("@dv3=Off") != -1){ digitalWrite(dv3Port,portOff); dv3St = "Off";}
  
  if(com.indexOf("@fan=On") != -1 ){ digitalWrite(fanPort,portOn); fanSt = "On";}
  if(com.indexOf("@fan=Off") != -1){ digitalWrite(fanPort,portOff); fanSt = "Off";}
  
  if(com.indexOf("@het=On") != -1){ digitalWrite(hetPort,portOn); HeatSec = "On";}
  if(com.indexOf("@het=Off") != -1){ digitalWrite(hetPort,portOff); HeatSec = "Off";}

  if(com.indexOf("@lig=On") != -1){ digitalWrite(ligPort,portOn); ligSt = "On";}
  if(com.indexOf("@lig=Off") != -1){ digitalWrite(ligPort,portOff); ligSt = "Off";}
  
  if(com.indexOf("@luv=On") != -1){ digitalWrite(luvPort,portOn); luvSt = "On";}
  if(com.indexOf("@luv=Off") != -1){ digitalWrite(luvPort,portOff); luvSt = "Off";}
  
}

void changeComCode(){
  String str="";
  //str += "@temp=@"+String(temperature);
  str += "@temp=@"+GetTemp();
  str += "@door=@"+GetDoor();
  
  str += "@co2="+co2St;
  str += "@o2="+o2St;
  str += "@n2="+n2St;
  
  str += "@dv1="+dv1St;
  str += "@dv2="+dv2St;
  str += "@dv3="+dv3St;
  
  str += "@het="+HeatSec;
  str += "@fan="+fanSt;
  
  str += "@lig="+ligSt;
  str += "@luv="+luvSt;
  wc.SetComSite(str);
}

String GetTemp(){
  if(temperature>0){
    
    double tempe = 0;
    for(int i=0;i<40;i++){
      tempe+=(temp.getTemp() *10);
      //if(tempe<10){ return "0.00";}
    }
    tempe=tempe/400;
    if(temperature>tempe-0.666){
      digitalWrite(hetPort,portOn);
    }else{
      if(temperature<tempe-0.606){
        digitalWrite(hetPort,portOff);
      }
    }
    if(tempe>100){
      return "0.0";
    }else{
      return String(tempe);
    }
  }
  return "0.0";
}

String GetDoor(){
  if(digitalRead(dorPort)==1){
    return "Closed";
    //fanSt="On";
  }else{
    //fanSt="Off";
    return "Open";
  }
}

