/*
  ESP8266 library

  Connection:
  When you use it with UNO board, the connection should be like these:

  ESP8266_TX->RX(D10)
  ESP8266_RX->TX(D11)
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

#include <SoftwareSerial.h>
#include "uartWIFIUNO.h"

WIFIUNO wifi;

extern int chlID;

// set pin numbers:
const int ledPin =  13;      // the number of the LED pin

const int relay1 =  2;
const int relay2 =  3;
const int relay3 =  4;
const int relay4 =  5;

boolean device1 = false;
boolean device2 = false;
boolean device3 = false;
boolean device4 = false;


void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  //pinMode(ESP8266_CHPD, OUTPUT);
  //digitalWrite(ESP8266_CHPD,LOW);

  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);

  DebugSerial.println("ESP8266 Server v0.21");
  if (!wifi.begin())
  {
    DebugSerial.println("Begin error");
  }
  bool b = wifi.Initialize(STA, SSID, PASSWORD);
  if (!b)
  {
    DebugSerial.println("Init error");
  }
  delay(8000);  //make sure the module can have enough time to get an IP address
  String ipstring  = wifi.showIP();
  DebugSerial.println(ipstring);		//show the ip address of module

  delay(1000);
  wifi.confMux(1);
  delay(100);
  if (wifi.confServer(1, 80))
    DebugSerial.println("Server is set up");

}

void loop()
{

  char buf[500];
  int iLen = wifi.ReceiveMessage(buf);

  if (iLen > 0)
  {

    DebugSerial.print(buf);
    //delay(300);

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



    String cmd;
    cmd = "HTTP/1.1 200 OK\r\n";
    cmd += "Content-Type: text/html\r\n";
    cmd += "Connection: close\r\n";
    //cmd += "Refresh: 15\r\n";
    cmd += "\r\n";
    //cmd += "<!DOCTYPE HTML>\r\n";
    cmd += "<html>\r\n";
    //cmd += "<header><title>ESP8266 Webserver</title><h1>\"ESP8266 Web Server Control\"</h1></header>";


    if (device1) {
      cmd += ("<br/>Device1  : ON");
    }
    else {
      cmd += ("<br/>Device1  : OFF");
    }

    if (device2) {
      cmd += ("<br/>Device2  : ON");
    }
    else {
      cmd += ("<br/>Device2  : OFF");
    }


    if (device3) {
      cmd += ("<br/>Device3  : ON");
    }
    else {
      cmd += ("<br/>Device3  : OFF");
    }

    if (device4) {
      cmd += ("<br/>Device4  : ON");
    }
    else {
      cmd += ("<br/>Device4  : OFF");
    }

    cmd += "<html>\r\n";

    wifi.Send(chlID, cmd);
    //delay(200);
    wifi.closeMux(chlID);
    //delay(1000);


  }
}
