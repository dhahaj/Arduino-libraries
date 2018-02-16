/**
 *  @brief WIFIUNO
 *  
 *  @param [in] 12 Parameter_Description
 *  @param [in] 11 Parameter_Description
 *  @param [in] 5  Parameter_Description
 *  @param [in] 4  Parameter_Description
 *  @param [in] 3  Parameter_Description
 *  @param [in] 2  Parameter_Description
 *  @return Return_Description
 *  
 *  @details Details
 */
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

WIFIUNO wifi;

extern int chlID;

// set pin numbers:
const int ledPin =  13;      // the number of the LED pin

const int relay1 =  22;
const int relay2 =  23;
const int relay3 =  24;
const int relay4 =  25;	

boolean device1 = false;
boolean device2 = false;
boolean device3 = false;
boolean device4 = false;

const int ESP8266_CHPD = 8;


boolean readyy = false;

int result = 0;
int OK = 1;
int TIMEOUT = 2 ;
int CANCEL = 3;
int NOT_FOUND = 4;

int i;
int m=0;
int lp = 0;

char inputChar[500];
int len = 0;


//String serverip="192.168.1.37";
String port="80";
String cmd;
String myIP;

int currentID;

int ch_id, packet_len;
char *pb;


void(* resetFunc) (void) = 0;                          //declare reset function at address 0








