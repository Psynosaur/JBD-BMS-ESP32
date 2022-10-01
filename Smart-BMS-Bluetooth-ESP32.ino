
#define TRACE

#include <Arduino.h>
#include "BLEDevice.h"

#include "mydatatypes.h"



HardwareSerial commSerial(0);
HardwareSerial bmsSerial(1);


//---- global variables ----

static boolean doConnect = false;
static boolean BLE_client_connected = false;
static boolean doScan = false;

packBasicInfoStruct packBasicInfo; //here shall be the latest data got from BMS
packEepromStruct packEeprom;	   //here shall be the latest data got from BMS
packCellInfoStruct packCellInfo;   //here shall be the latest data got from BMS

const byte cBasicInfo3 = 3; //type of packet 3= basic info
const byte cCellInfo4 = 4;  //type of packet 4= individual cell info

unsigned long previousMillis = 0;
const long interval = 500;

bool toggle = false;
bool newPacketReceived = false;

void setup()
{

	commSerial.begin(115200, SERIAL_8N1, 3, 1);
	bmsSerial.begin(9600, SERIAL_8N1, 21, 22);
	commSerial.println("Starting BMS serial dashboard");
	bleStartup();
}
//---------------------main loop------------------
void loop()
{
	bleRequestData();
	if (newPacketReceived == true)
	{
		printBasicInfo();
		printCellInfo();
    delay(interval);
	} 
}
//---------------------/ main loop------------------
