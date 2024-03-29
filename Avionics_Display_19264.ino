/* Experimental Avionics Display module ver 3.0*/
/* This module combines EFIS and EMS functionality together */

#include <Time.h>
#include <EEPROM.h>
#include <openGLCD.h>
#include <openGLCD_Buildinfo.h>
#include <openGLCD_Config.h>
#include "Wire.h"
#include "RTClib.h"
#include <math.h>
#include <Encoder.h>
//#include <SPI.h>
#include "mcp_can.h"

// LCD backight control stuff
const int BacklightControlPin = 6; //D6
const int BacklightSensorPin = A8;
unsigned int BacklightSensorReading = 0; // ADC reading
unsigned int BacklightBrightness = 0; // LCD screen brightness, analog reading devided by 4
unsigned int LEDBrightness = 0; // Warning LEDs brightness

//EMS Sensor Board configuration - 4 or 6 cylinders engine
const int CYL = 4;

// CAN related stuff
const int SPI_CS_PIN = 49;
unsigned long canId;
MCP_CAN CAN(SPI_CS_PIN);  

unsigned char len = 0;
unsigned char buf[8];
unsigned char ext = 0;

//#define DS3231_I2C_ADDRESS 0x68   //clock
RTC_DS1307 RTC;

// Alarms
unsigned long RedBlinkTimer = 0;
unsigned long YellowBlinkTimer = 0;


// EMS related variables
unsigned int RPM = 0;
unsigned int FuelFlow = 0;
unsigned int FuelPressure = 0;
unsigned int TankLevel1 = 0;
//unsigned int TankLevel2 = 0;
unsigned int OilTemperature = 0;
unsigned int OilPressure = 0;
unsigned int EGT[7] = {0,0,0,0,0,0,0}; // first two bytes will be wasted for the sake of convenience and clarity :)
unsigned int CHT[7] = {0,0,0,0,0,0,0};
unsigned int EL_Volts = 0;
int EL_BatAmps = 0;
int EL_AltAmps = 0;
unsigned long TT_RPM = 0;
unsigned long TT_Clock = 0;
unsigned long UnixTime = 0;

unsigned int BAT_Volts = 0;
int BAT_Temperature = 0;
byte BAT_Status = 0;

// EFIS related variables
//*************** Text areas ***/************
gText textAreaIAS;
gText textAreaSPEED;
gText textAreaKTS;

gText textAreaHDG;
gText textAreaMAG;
gText textAreaDEG;
gText textAreaMagCal;

gText textAreaTimeMaster;
gText textAreaUTC;
gText textAreaUTCTime;
gText textAreaFLT;
gText textAreaFLTTime;

gText textAreaBottomL;
gText textAreaBottomR;
gText textAreaGmeter;

gText textAreaALTFT;    
gText textAreaALT;      
gText textAreaVSI;      
gText textAreaVSIvalue;  
gText textAreaVSIarrow;  
gText textAreaQNH;
gText textAreaQNHvalue;

gText textAreaGS;
gText textAreaGSvalue;
gText textAreaGPSalt;
gText textAreaGPSaltvalue;
gText textAreaGPSDATA;
gText textAreaGPSTRK;
gText textAreaGPSTRKvalue;
gText textAreaGPSsats;
gText textAreaGLONASSsats;

gText textAreaTASDATA;
gText textAreaOAT;
gText textAreaOATvalue;
gText textAreaTAS;
gText textAreaTASvalue;
gText textAreaWND;
gText textAreaWNDdirection;
gText textAreaWNDspeed;

//***********MENU*************
gText textAreaSetting0;
gText textAreaSetting1;
gText textAreaSetting2;
gText textAreaSetting3;
gText textAreaSetting4;

//********** EMS **************

//*********** Fuel flow ***************
gText textFlowLabel;
gText textEndurLabel;
gText textFlowActual;
gText textFlowPlanned;
gText textEndurActual;
gText textEndurPlanned;

//******** EMS Alt Right Screen *******
gText textAreaEMSAltKey1;
gText textAreaEMSAltValue1;
gText textAreaEMSAltLabel1;

gText textAreaEMSAltKey2;
gText textAreaEMSAltValue2;
gText textAreaEMSAltLabel2;

gText textAreaEMSAltKey3;
gText textAreaEMSAltValue3;
gText textAreaEMSAltLabel3;

gText textAreaEMSAltKey4;
gText textAreaEMSAltValue4;
gText textAreaEMSAltLabel4;

gText textAreaEMSAltKey5;
gText textAreaEMSAltValue5;
gText textAreaEMSAltLabel5;

gText textAreaEMSAltKey6;
gText textAreaEMSAltValue6;
gText textAreaEMSAltLabel6;

//******** EMS Backup Battery Section *******
gText textBatVoltLabel;
gText textBatVoltValue;
gText textBatTempValue;
gText textBatStatus;




int MidScreen = 0;    // alternative screen for EFIS (GPS data, etc)
int RightScreen = 0;  // alternative screen for EMS (on the right side)
unsigned long int RightScreenTimer = 0;

unsigned int  Airspeed = 0; //Airspeed
unsigned int Airspeed_old = 0;
unsigned int Altitude = 0;
unsigned int Altitude_old = 0;
int VertSpeed = 0;
int VertSpeed_old = 0;
int AOA = 0;

int OAT = 0;
int OAT_old = 0;
int Humidity = 0;
int TAS = 0;
int TAS_old = 0;

unsigned int RawPressure = 0;
float Delta = 0;

unsigned int HDG = 0;
unsigned int HDG_old = 0;
int Roll = 0;
int Pitch = 0;
int TurnRate = 0; 

int AccX = 0;
int AccY = 0;
int AccZ = 0;
unsigned int CalibrationStats = 0;
unsigned int CalibrationStats_old = 0;

unsigned int GroundSpeed = 0;
unsigned int GPSaltitude = 0;
int TrackingTrue = 0;
int TrackingMagnetic = 0;
String Tracking = "M 000";
byte Sat_SN[8];

unsigned long TimeRefresh = 0;
unsigned long FlightStartMarker = 0;
unsigned long FlyingTime = 0;
unsigned long FlyingTimePrevious = 0;
String s_FlightTime = "";

//**********************************  AH ************************************************************
int  yStartOld = 26, yEndOld = 26, xStartOld = 96, xEndOld = 96, xBugOld = 80, yBugOld = 10, xBallOld = 96;
int xm60_old = 68, ym60_old = 3;
int xm30_old = 68, ym30_old = 3;
int xp60_old = 68, yp60_old = 3;
int xp30_old = 68, yp30_old = 3;

//*********** encoder *****************
Encoder myEnc(18, 19);
const int Click_Button = 3;
unsigned long bTimer = 0;
int buttonState = 0, MenuItem = 0, encLastValue = 0;

//**************** EEPROM *******************
int QNH = 1013;
int QNH_MemOffset = 0;
int MinFlightSpeed = 20;          // Airspeed that triggers flight timer
int MinFlightSpeed_MemOffset = 2; // two bytes (int) for storing min flight switch
byte TimeConfig = 0;              // Time UTC or Local UTC = 0, Local = 1
int TimeConfig_MemOffset = 4;     // 
byte TimeMaster = 1;
int TimeMaster_MemOffset = 5; 
unsigned long  TimeSendPeriod = 15000;
unsigned long  TimeSendTimestamp = 0;
unsigned long  TimeReceiveTimestamp = 0;



// Both EMS and EFIS related stuff
unsigned long LoopTimer = 0;

// Flag controlling which screen to display
// 1 - EFIS
// 2 - EMS
// 3 - something else
unsigned int DisplayScreen = 1;
unsigned int ScreenChange = 1;  // Variable to track display changes

byte ForceDisplay = 1;

//*************** Text areas ***/************
gText textAreaRPM;




void setup() {
  Wire.begin();
  Serial.begin(115200);
  RTC.begin();

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
  }

  // Adjust the clock to the current time from PC (at compilation)
  // RTC.adjust(DateTime(__DATE__, __TIME__));


  // EFIS or EMS?????
  pinMode(44, INPUT_PULLUP);          // pull up digital pin 44
  if (digitalRead(44) == LOW) {
    DisplayScreen  = 2;
  }

  //Alam LEDs
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);


    //while (CAN_OK != CAN.begin(MCP_ANY, CAN_1000KBPS, MCP_8MHZ))              // init can bus : baudrate = 500k
    while (CAN_OK != CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ))
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(500);
    }
    CAN.setMode(MCP_NORMAL);
    Serial.println("CAN BUS Shield init ok!");


// there are 2 mask in mcp2515, you need to set both of them
//    CAN.init_Mask(0,0,0x410);
//    CAN.init_Mask(1,0,0x410); // 100 0001 0000
//    CAN.init_Filt(0,0,0x3FF); // 011 1111 1111
    
  RedLightBlink(1);
  YellowLightBlink(1);

  analogWrite(BacklightControlPin, 128);

  GLCD.Init();
   
    GLCD.ClearScreen();
    GLCD.SelectFont(System5x7);
    GLCD.CursorTo(5, 2);
    GLCD.print("Experimental Avionics");
    GLCD.CursorTo(9, 4);
    GLCD.print("Display System");
    GLCD.CursorTo(10, 6);
    GLCD.print("2023-12-14");
    delay(2000);
    GLCD.ClearScreen();

  RedLightBlink(0);
  YellowLightBlink(0);

  // DisplayScreen = 1;  
    Init_Screen();

}

void loop() {

  // check for LCD brightness adjustments
   BacklightSensorReading = analogRead(BacklightSensorPin);
   if (BacklightSensorReading < 100) {
    BacklightBrightness = 0;
   } else {
    BacklightBrightness = (BacklightSensorReading - 100)/4;
    
   }

   if (BacklightSensorReading > 900) {
    //BacklightSensorReading = 1024;
    BacklightBrightness = 255;
   } 

  // LED brigness need to be somewhat lower when LCD brightness is below half-full
  // It also should never go down to Zero

  if (BacklightBrightness < 192) {
    LEDBrightness = BacklightBrightness / 4;
  } else {
    LEDBrightness = BacklightBrightness;
  }
  if (BacklightBrightness < 10) {
    LEDBrightness = 2;
  }


   
   analogWrite(BacklightControlPin, BacklightBrightness);
  //analogWrite(BacklightControlPin, 10);
  
  // send the time periodically if this unit is the time master
  if (millis() - TimeSendTimestamp > TimeSendPeriod and TimeMaster == 1) {
    SendTime();
    TimeSendTimestamp = millis(); 
  }

// if this unit is not a time master and no system time message arrived over last 120 seconds, self-promote to time master
  if (millis()-TimeReceiveTimestamp > 120000 and TimeMaster == 0) {
    TimeMaster = 1;
    EEPROM.put(TimeMaster_MemOffset, 1);
    textAreaTimeMaster.print("*");
    Serial.println("The unit is self-promoted to a Time Master");
  }
  

  if (digitalRead(44) == LOW and DisplayScreen == 1) {
    DisplayScreen  = 2;
    ForceDisplay = 1;
    Init_Screen();
    //Serial.print("DisplayScreen: ");
    //Serial.println(DisplayScreen);
  }

  if (digitalRead(44) == HIGH and DisplayScreen == 2) {
    DisplayScreen  = 1;
    ForceDisplay = 1;
    Init_Screen();
    //Serial.print("DisplayScreen: ");
    //Serial.println(DisplayScreen);
  }

  // Airspeed=60; 

  if (Airspeed > MinFlightSpeed and FlightStartMarker == 0) { //we reached flying speed and it is time to start the timer
    FlightStartMarker = millis();
  }

  if (Airspeed > MinFlightSpeed and FlightStartMarker > 0) { //we are flying so keep track of the time
    FlyingTime = FlyingTimePrevious + millis() - FlightStartMarker;
  }

  if (Airspeed <= MinFlightSpeed) { //we are flying so keep track of the time
    FlyingTimePrevious = FlyingTime;
    FlightStartMarker = 0;
  }
  

switch (DisplayScreen) {
      case 1:   // EFIS
          EFIS_Main();
          if (millis()-TimeRefresh>1000){
            TimeRefresh = millis();
            FlightTime();
          }
          break;
      case 2:   // EMS
          EMS_Main();
          break;
  }

  Warning_lights();
}

// Send current time if this unit is Master time keeper
void SendTime() {
  DateTime now = RTC.now();
  UnixTime = now.unixtime();
//  Serial.print("Sending System Time ");
//  Serial.println(UnixTime);
  buf[0] = UnixTime;
  buf[1] = UnixTime >> 8;
  buf[2] = UnixTime >> 16;
  buf[3] = UnixTime >> 24;
  CAN.sendMsgBuf(25, 0, 4, buf);
  
 Serial.println(((unsigned long)buf[3] << 24) | ((unsigned long)buf[2] << 16) | ((unsigned long)buf[1] << 8) | (unsigned long)buf[0]);

}

void ReceiveTime() {
  TimeReceiveTimestamp = millis();
  UnixTime = ((unsigned long)buf[3] << 24) | ((unsigned long)buf[2] << 16) | ((unsigned long)buf[1] << 8) | (unsigned long)buf[0];
  Serial.print("Received Unix Time ");
  Serial.println(UnixTime);
  DateTime now = RTC.now();
  if (abs(now.unixtime()- UnixTime) > 30) {
    RTC.adjust(DateTime(UnixTime));
  }
  
  // if this is the first system time message, turn off TimeMaster flag and record it into the EEPROM
  if (TimeMaster == 1) {
    EEPROM.put(TimeMaster_MemOffset, 0);
    TimeMaster = 0;
    textAreaTimeMaster.print(" ");
    Serial.println("The unit is no longer a Time master");
  }
  }
