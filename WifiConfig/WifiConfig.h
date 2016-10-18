/*/
 *   Created by TTOExtreme in 08-09-2016
/*/

#ifndef WifiConfig_h
#define WifiConfig_h

#include "Arduino.h"
#include "SerialCom.h"
//includes for esp8266
#include "EEPROM.h"
#include "ESP8266WebServer.h"

class WifiConfig {
	public:
		WifiConfig();
		
		void SetComPort(int comPort);
		
		void Init();
		void Exec();//executes the program(put this func in "void loop")
		
		void SetComSite(String htmlCode);
		void SetIpEnd(int ipEnd);
		void useAltComSite(bool useAlt);
		String GetCommandRecieved();
		//funçoes auxiliares
		String GetComSite();
		String GetSetupSite();
		int _ipend=177;
	private:
	
		void ExecCommands(String com);//get and executes commands  
		void writeCfg(String Ssid,String Pass);
		String loadCfgSSID();
		String loadCfgPASS();
		void handleCfgRoot();
		void handleComRoot();
		void OpenConfigNetwork();
		void OpenComNetwork();
		bool ConnectTo(String newSSID,String newPASS);
		
		ESP8266WebServer cfgserver=ESP8266WebServer(80);//to config the dispositive
		ESP8266WebServer comserver=ESP8266WebServer(5546);//to send commands
		String ssidConfig = "ConfigNet";
		int _ComPort=5546;
		
		String altComSiteCode="";
		String LastCommand="";
		bool altComSite=false;
		bool isConfig=false;
		bool debug = false;
		//comunication
		//***********************************************************
		//String _password="123456";
		int _baudRate=115200;
		char _first='#';//first char of receptor not used
		char _last=';';//final char of receptor not used
		SerialCom Com=SerialCom(_baudRate, _first, _last);
		//***********************************************************
		
};

#endif