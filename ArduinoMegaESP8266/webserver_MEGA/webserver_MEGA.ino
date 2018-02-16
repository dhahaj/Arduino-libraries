/*
ESP8266 library


When you use it with MEGA board, the connection should be like these:
ESP8266_TX->RX1(D19)
ESP8266_RX->TX1(D18)
ESP8266_CH_PD->3.3V
ESP8266_VCC->3.3V
ESP8266_GND->GND


When you want to output the debug information, please use DebugSerial. For example,

DebugSerial.println("hello");


Note:	The size of message from ESP8266 is too big for arduino sometimes, so the library can't receive the whole buffer because  
the size of the hardware serial buffer which is defined in HardwareSerial.h is too small.

Open the file from \arduino\hardware\arduino\avr\cores\arduino\HardwareSerial.h.
See the follow line in the HardwareSerial.h file.

#define SERIAL_BUFFER_SIZE 64

The default size of the buffer is 64. Change it into a bigger number, like 256 or more.

*/


//#define SSID       "dlink"
//#define PASSWORD   "0814931872"

#define SSID       "SmartHome"
#define PASSWORD   "0816452400"

#include "uartWIFIUNO.h"
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include "declare.h"


void setup()
{
  pinMode(ledPin, OUTPUT); 
  pinMode(relay1, OUTPUT); 
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  
  //pinMode(ESP8266_CHPD, OUTPUT);
  //digitalWrite(ESP8266_CHPD,LOW);
  
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,LOW);
  digitalWrite(relay3,LOW);
  digitalWrite(relay4,LOW);
  
   DebugSerial.println("ESP8266 Server v0.2");
   
   // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);  
  lcd.print("ESP8266 Control");            // Print a message to the LCD.
  
  lcd.setCursor(0,1);                               // set the cursor to (16,1):
  lcd.print("Init...");                             // Print a message to the LCD.
  
  
  if(!wifi.begin())
  {
  	DebugSerial.println("Begin error");
  }
  bool b = wifi.Initialize(STA, SSID, PASSWORD);
  if(!b)
  {
    DebugSerial.println("Init error");
     resetFunc();
    
    
  }
  delay(8000);  //make sure the module can have enough time to get an IP address 
  String ipstring  = wifi.showIP();
  DebugSerial.println(ipstring);		//show the ip address of module
        lcd.setCursor(0,0);                               // set the cursor to (16,1):
        lcd.print(ipstring);
  
  delay(1000);
  wifi.confMux(1);
  delay(100);
  if(wifi.confServer(1,80))
	DebugSerial.println("Server is set up");

        lcd.setCursor(0,1);                               // set the cursor to (16,1):
        lcd.print("Start Server"); 
        lcd.setCursor(0,1);                               // set the cursor to (16,1):
        lcd.print("online      "); 
	

}
void loop()
{
  
  char buf[500];
  int iLen = wifi.ReceiveMessage(buf);
  
  if(iLen > 0)
  {
    
      DebugSerial.print(buf);
      //delay(100);
          
       if (strncmp(buf, "GET /?status1=1", 15) == 0) {               
           //DebugSerial.print("RELAY 1 ON");
           digitalWrite(relay1, HIGH); 
           device1 = true;           
       }   
       else if (strncmp(buf, "GET /?status1=0", 15) == 0) {               
           //DebugSerial.print("RELAY 1 OFF");
           digitalWrite(relay1, LOW); 
           device1 = false;           
       } 
                
    
    if (strncmp(buf, "GET /?status2=1", 15) == 0) {               
           //DebugSerial.print("RELAY 2 ON");
           digitalWrite(relay2, HIGH); 
           device2 = true;           
       }   
       else if (strncmp(buf, "GET /?status2=0", 15) == 0) {               
           //DebugSerial.print("RELAY 2 OFF");
           digitalWrite(relay2, LOW); 
           device2 = false;           
       } 
       
       
       if (strncmp(buf, "GET /?status3=1", 15) == 0) {               
           //DebugSerial.print("RELAY 3 ON");
           digitalWrite(relay3, HIGH); 
           device3 = true;           
       }   
       else if (strncmp(buf, "GET /?status3=0", 15) == 0) {               
           //DebugSerial.print("RELAY 3 OFF");
           digitalWrite(relay3, LOW); 
           device3 = false;           
       } 
       
       if (strncmp(buf, "GET /?status4=1", 15) == 0) {               
           //DebugSerial.print("RELAY 4 ON");
           digitalWrite(relay4, HIGH); 
           device4 = true;           
       }   
       else if (strncmp(buf, "GET /?status4=0", 15) == 0) {               
           //DebugSerial.print("RELAY 4 OFF");
           digitalWrite(relay4, LOW); 
           device4 = false;           
       } 
      
      
      String cmd;
      cmd = "HTTP/1.1 200 OK\r\n";
      cmd += "Content-Type: text/html\r\n";
      cmd += "Connection: close\r\n";
      cmd += "Refresh: 15\r\n";
      cmd += "\r\n";
      cmd += "<!DOCTYPE HTML>\r\n";
      cmd += "<html>\r\n";
      //cmd += "<header><title>ESP8266 Webserver</title><h1>\"ESP8266 Web Server Control\"</h1></header>";
      
      
      if(device1){
        cmd +=("<br/><h2>Device1  : ON</h2>");
      }
      else{
        cmd +=("<br/><h2>Device1  : OFF</h2>");
      }
      
      if(device2){
        cmd +=("<br/><h2>Device2  : ON</h2>");
      }
      else{
        cmd +=("<br/><h2>Device2  : OFF</h2>");
      }
      
      
       if(device3){
        cmd +=("<br/><h2>Device3  : ON</h2>");
      }
      else{
        cmd +=("<br/><h2>Device3  : OFF</h2>");
      }
      
      if(device4){
        cmd +=("<br/><h2>Device4  : ON</h2>");
      }
      else{
        cmd +=("<br/><h2>Device4  : OFF</h2>");
      }
      
      
      cmd += "<html>\r\n";

        wifi.Send(chlID,cmd);
        //delay(100);
        wifi.closeMux(chlID);
	//delay(1000);

  }
}
