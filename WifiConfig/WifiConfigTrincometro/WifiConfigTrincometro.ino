/*/
 *   Created by TTOExtreme in 08-09-2016
/*/

#include <WifiConfig.h>
#include <Thermistor.h>

WifiConfig wc;

const byte tmpPort = A0;//temperature

double temperature=0.0;

Thermistor temp(tmpPort);

void setup() {
  Serial.begin(115200);
  wc.Init();
  pinMode(tmpPort,INPUT); 
}

void loop() {
  //temperature=GetTemp().toFloat();
  changeComCode();//sets the comunication code every time
  wc.Exec();
  PortControl(wc.GetCommandRecieved());
}

void PortControl(String com){
  if(com.indexOf("@temp") != -1){ 
    temperature=GetTemp().toFloat();
    //temperature=((com.substring(com.indexOf("@temp=") + 6)).toFloat());
    //Serial.println("temperature get: " + String(temperature));
  }
}

void changeComCode(){
  String str="";
  str += "@temp=@"+String(temperature);
  wc.SetComSite(str);
}

String GetTemp(){
    double tempe = 0;
    //for(int i=0;i<40;i++){
      tempe=(temp.getTemp());
    //}
    //tempe=tempe/40;
    Serial.print("Temperature: ");
    Serial.println(String(tempe));
  return String(tempe);
}

