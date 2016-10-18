/*/
 *   Created by TTOExtreme in 08-09-2016
/*/

#include "Arduino.h"
#include "WifiConfig.h"
#include "SerialCom.h"
#include "EEPROM.h"
#include "ESP8266WebServer.h"
//#include "StepMotor4988.h"

WifiConfig::WifiConfig(){
	cfgserver = ESP8266WebServer(80);//default port
	comserver = ESP8266WebServer(5546);//port to transfer data
}

void WifiConfig::SetComPort(int comPort){
	_ComPort=comPort;
	
	cfgserver = ESP8266WebServer(80);//default port
	comserver = ESP8266WebServer(comPort);
}

void WifiConfig::Init(){
	if(debug){Com.Send("Initializing");}
  
	EEPROM.begin(512);
	/* //to clear for first execution
	for (int i = 0; i < 94; i++){ EEPROM.write(i, 0); }
    EEPROM.commit();
	//*/  
	if(char(EEPROM.read(0))==char(95)){//if is configured
		if(debug){Com.Send("is cofigured");}
		isConfig=true;
		ConnectTo(loadCfgSSID(),loadCfgPASS());
		if(isConfig==true){
		}
	}
	OpenConfigNetwork();
	OpenComNetwork();
}

void WifiConfig::Exec(){ //function called in the loop
	cfgserver.handleClient();
	//if(!isConfig){ return; }
	comserver.handleClient();
}

//****************************************************************************************************************\\

//****************************************************************************************************************\\
//commands
void WifiConfig::ExecCommands(String com){
	if(debug){Com.Send("Command recieved: " + com);}
	LastCommand=com;
	if(com=="clearcfg"){
		if(debug){Com.Send("Clearing the eeprom");}
    
		for (int i = 0; i < 94; i++){ EEPROM.write(i, 0); }
		EEPROM.commit();
    
		isConfig=false;
		OpenConfigNetwork();
	}
	if(com=="nAltCom"){//deactivates the alternative com site
		if(debug){Com.Send("deactivating the alternative com site");}
		useAltComSite(false);
	}
	if(com=="uAltCom"){//activates the alternative com site
		if(debug){Com.Send("activating the alternative com site");}
		useAltComSite(true);
	}
}
//****************************************************************************************************************\\

//****************************************************************************************************************\\
//WR the config in eeprom
void WifiConfig::writeCfg(String Ssid,String Pass){
	const char* _ssid=Ssid.c_str();
	const char* _pass=Pass.c_str();
	//if(debug){Com.Send("write ssid: ");}
  
	for (int i = 0; i < 94; i++){ EEPROM.write(i, 0); }
  
  
	EEPROM.write(0,char(95));
	int i=0;
	for(i=0;i<Ssid.length();i++){
		//Serial.print(_ssid[i]);}
		EEPROM.write(i+1,_ssid[i]);
	}
	EEPROM.write(i+2,char('#'));
  
	//if(debug){Com.Send(" i value:" + String(i));}
	//if(debug){Com.Send(" ");}
	//if(debug){Com.Send("write pass: ");}
	int j=0;
	for(j=0;j<Pass.length();j++){
		// Serial.print(_pass[j]);}
		EEPROM.write(j+3+i,_pass[j]);
	}
	EEPROM.write(i+3+j,char('@'));
  
	//if(debug){Com.Send(" ");}
	if(debug){Com.Send("commiting");}
	EEPROM.commit();
}
String WifiConfig::loadCfgSSID(){
	String strssid="";
	//if(debug){Com.Send("load ssid: ");}
	int i=0;
	while(char(EEPROM.read(i+1))!=char('#') && i<94){
		//if(debug){Com.Send(str);}
		strssid += char(EEPROM.read(i+1));
		i++;
	}
	//if(debug){Com.Send(strssid);}
	//if(debug){Com.Send(" ");}
	return strssid;
}
String WifiConfig::loadCfgPASS(){
	String strpass="";
	//if(debug){Com.Send("load password: ");}
	int i=0;
	while(char(EEPROM.read(i+1))!=char('#') && i<94){ i++; }//up to the pass
	//if(debug){Com.Send("vpos: " + String(i));}
	while(char(EEPROM.read(i+2))!=char('@') && i<94){
		//if(debug){Com.Send(str);}
		strpass += char(EEPROM.read(i+2));
		i++;
	}
	//if(debug){Com.Send(strpass);}
	//if(debug){Com.Send(" ");}
	return strpass;
}

//****************************************************************************************************************\\

//****************************************************************************************************************\\
//handles for the sites

void WifiConfig::handleCfgRoot() {
    char temp[420];
    cfgserver.send( 200,temp,GetSetupSite());
    
    String newSSID = cfgserver.arg("ssid");
    String newPASS = cfgserver.arg("pass");
    if(debug){Com.Send("SSID: " + newSSID);}
    if(debug){Com.Send("Password: " + newPASS);}
    if(newSSID!="" && newPASS!=""){
		isConfig=true;
		if(!ConnectTo(newSSID,newPASS)){ if(debug){Com.Send("Failed!");} EEPROM.write(0,char(2)); EEPROM.commit();}
		writeCfg(newSSID,newPASS);
		OpenComNetwork();
    }
}
void WifiConfig::handleComRoot(){
	String Command = comserver.arg("comma");
	ExecCommands(Command);
	
	char temp[420];
	comserver.send( 200,temp,GetComSite());
}

//****************************************************************************************************************\\

//****************************************************************************************************************\\
//opens the sites
void WifiConfig::OpenConfigNetwork(){
    if(isConfig==false){
		//WiFi.disconnect();
		//WiFi.mode(WIFI_AP);
	
		WiFi.softAP(ssidConfig.c_str());
		
		IPAddress myIP = WiFi.softAPIP();
		if(debug){Com.Send("AP IP address: ");}
		if(debug){Com.Send((myIP).toString());}
    }
    cfgserver.on("/", std::bind(&WifiConfig::handleCfgRoot, this));
    cfgserver.begin();
    if(debug){Com.Send("HTTP cfg server started");}
}
void WifiConfig::OpenComNetwork(){
    IPAddress myIP = WiFi.localIP();
    comserver.on("/data", std::bind(&WifiConfig::handleComRoot, this));
    comserver.begin();
    if(debug){Com.Send("HTTP server started");}
    if(debug){Com.Send("loaded ssid: " + loadCfgSSID());}
    if(debug){Com.Send("loaded Password: " + loadCfgPASS());}
    int i=0;
	String str="";
    while(i<96){
		str+=char(EEPROM.read(i));
		i++;
    }
    if(debug){Com.Send("eeprom: " + str);}
    if(debug){Com.Send(" ");}
}

bool WifiConfig::ConnectTo(String newSSID,String newPASS){
	WiFi.mode(WIFI_STA);
	WiFi.disconnect();
	WiFi.begin(newSSID.c_str(),newPASS.c_str());
	
	int c=0;
	while(WiFi.status()!=WL_CONNECTED){
		c++;
		if(c>30){ if(debug){Com.Send("Failed!");} isConfig=false; OpenConfigNetwork(); return false; }
		delay(300);
		//if(debug){Com.Send(".");}
	}
	
	String ipget = WiFi.localIP().toString();
	if(debug){Com.Send("Connecting to get data " + ipget);}
	int ip1 = ipget.substring(0,ipget.indexOf(".")).toInt();
	ipget = ipget.substring(ipget.indexOf(".")+1);
	int ip2 = ipget.substring(0,ipget.indexOf(".")).toInt();
	ipget = ipget.substring(ipget.indexOf(".")+1);
	int ip3 = ipget.substring(0,ipget.indexOf(".")).toInt();
	IPAddress ip(ip1, ip2, ip3, _ipend);  
	IPAddress gateway(ip1, ip2, ip3, 1);  
	IPAddress subnet(255, 255, 255, 0);  
	
	WiFi.mode(WIFI_STA);
	WiFi.disconnect();
	if(debug){Com.Send("Connecting to get data " + (String(_ipend)));}
	
	WiFi.config(ip, gateway, subnet);
	WiFi.begin(newSSID.c_str(),newPASS.c_str());
	c=0;
	if(debug){Com.Send("Connecting");}
	while(WiFi.status()!=WL_CONNECTED){
		c++;
		if(c>30){ if(debug){Com.Send("Failed!");} isConfig=false; OpenConfigNetwork(); return false; }
		delay(300);
		//if(debug){Com.Send(".");}
	}
	if(debug){Com.Send("");}
	if(debug){Com.Send("Connected");}
	return true;
}

//****************************************************************************************************************\\

//****************************************************************************************************************\\
//sites codes (Default)
String WifiConfig::GetComSite(){
	if(altComSite){
		return altComSiteCode;
	}else{
		String str="";
		str ="this is the default com data site";
		return str;
	}
}
String WifiConfig::GetSetupSite(){//returns the html setup site
    String str="";
    str="<html>\
			<head>\
				<title>Configuration</title>\
			</head>\
			<div class='headerbg'></div>\
			<div class='headerbg1'></div>\
			<div class='headerbg2'></div>\
			<div class='header' >\
				<body>\
					<pre><font color='red'><h1> Setup for WIFI</h1></font></pre>\
					<hr color='blue' />\
				</body>\
			</div>\
			<div class='BackGround'></div>\
			<div class='BackGround1'></div>\
			<div class='BackGround2'></div>\
			<div class='bg'>\
				<body>\
					<br>";
					if(isConfig){
						str+="<form action'http://" + (WiFi.localIP()).toString() + "' method='get'>";
					}else{
						str+="<form action'http://" + (WiFi.softAPIP()).toString() + "' method='get'>";
					}
					str+="<font color='red'><pre> Ssid:     <input type='text' name='ssid'><br></pre></font>\
						<font color='red'><pre> Password: <input type='text' name='pass'><br></pre></font>\
						<pre> <input type='submit' value='    Save    '></pre>\
					</form>\
				</body>\
			</div>\
			<style>\
				.headerbg {position: absolute; top: 0px; left: 0px; width: 100%; height: 75px; background-color: #191919; }\
				.headerbg1 { position: absolute; top: 0px; left: 0px; width: 100%; height: 75px; background: -webkit-repeating-linear-gradient(45deg, rgba(0, 0, 0, 1) 5px, rgba(0, 0, 0, 1) 9px, rgba(50, 50, 50, 1) 9px, rgba(19, 19, 19, 1) 11px, rgba(19, 19, 19, 1) 30px, rgba(0, 0, 0, 1) 40px); }\
				.headerbg2 { position: absolute; top: 0px; left: 0px; width: 100%; height: 75px; background: -webkit-repeating-linear-gradient(-45deg, rgba(0, 0, 0, 1) 5px, rgba(0, 0, 0, 0) 15px, rgba(0, 0, 0, 0) 30px, rgba(0, 0, 0, 1) 34px, rgba(50, 50, 50, 1) 35px, rgba(19, 19, 19, 1) 36px, rgba(0, 0, 0, 1) 40px); }\
				.header { position: absolute; top: 0px; left: 0px; width: 100%; height: 75px; }\
				.topleft { position: absolute; top: 0px; left: 10px; width: 100%; height: 100%; font-size: 18px; background-color: rgba(0, 0, 0, 0); }\
				.bg { position: absolute; top: 75px; left: 0px; width: 100%; height: 100%; font-size: 18px; background-color: rgba(0, 0, 0, .65); }\
				.BackGround {position: absolute; top: 75px; left: 0px; width: 100%; height: 100%; background-color: #191919; }\
				.BackGround1 { position: absolute; top: 75px; left: 0px; width: 100%; height: 100%; background: -webkit-repeating-linear-gradient(45deg, rgba(0, 0, 0, 1) 5px, rgba(0, 0, 0, 1) 9px, rgba(50, 50, 50, 1) 9px, rgba(19, 19, 19, 1) 11px, rgba(19, 19, 19, 1) 30px, rgba(0, 0, 0, 1) 40px);}\
				.BackGround2 { position: absolute; top: 75px; left: 0px; width: 100%; height: 100%; background: -webkit-repeating-linear-gradient(-45deg, rgba(0, 0, 0, 1) 5px, rgba(0, 0, 0, 0) 15px, rgba(0, 0, 0, 0) 30px, rgba(0, 0, 0, 1) 34px, rgba(50, 50, 50, 1) 35px, rgba(19, 19, 19, 1) 36px, rgba(0, 0, 0, 1) 40px); }\	
			</style>\
		</html>";
   return str;
}

//****************************************************************************************************************\\

//****************************************************************************************************************\\
//User configs and gets
void WifiConfig::SetIpEnd(int ipEnd){
	_ipend=ipEnd;
	if(debug){Com.Send("Set IpEnd: " + String(_ipend));}
}

void WifiConfig::SetComSite(String htmlCode){
	altComSiteCode=htmlCode;
	altComSite=true;
}

void WifiConfig::useAltComSite(bool useAlt){
	altComSite=useAlt;
}

String WifiConfig::GetCommandRecieved(){
	String last=LastCommand;
	LastCommand="";
	return last;
}