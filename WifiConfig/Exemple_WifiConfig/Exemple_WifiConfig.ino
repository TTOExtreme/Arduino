/*/
 *   Created by TTOExtreme in 08-09-2016
/*/

#include <WifiConfig.h>
WifiConfig wc;

void setup() {
  wc.Init();
  changeComCode();//sets the comunication code once
}

void loop() {
  //changeComCode();//sets the comunication code every time
  wc.Exec();
}

void changeComCode(){
  String str="{'employees':[{'firstName':'John', 'lastName':'Doe'},{'firstName':'Anna', 'lastName':'Smith'},{'firstName':'Peter', 'lastName':'Jones'}]}";

  wc.SetComSite(str);
}

