void EFIS_Menu() {
// this routine has its own loop and nothing outside of it gets executed

 int SettingItem = 0;
 int ButtonPush = 0;
 int KeepLoop = true;
 int KeepLoop1 = true;
 int KeepLoop2 = true;
 int KeepLoop3 = true;
 int encCurrentValue = 0;
 int highlightwidth = 192;
 int highlighthight = 10;
 int textShiftX = 4;
 int textShiftY = 10;
 int MaxSettings = 4;  // number of setting items 
 byte second, minute, hour, dayOfWeek, dayOfMonth, month;
 int year;
 int secvalue = 0;
 int TimeSetPosition = 0;

// int CalCurrValue = 0;
// String CalDataCurrentString =""; // current calibration data
// String CalDataNewString =""; // temporary storage for current (latest) calibration data
 String CalFlag = "Y";

 byte calSys = 0;
 byte calGyro = 0;
 byte calAccel = 0;
 byte calMag = 0;
 byte CalibrationStats_old = 255;  



 String StringSetting1 = "";
 String StringSetting2 = "";
 String StringSetting3 = "";
 int tmpValue = 0;
 int tmpMinValue = 0;
 int tmpMaxValue = 0;
   
  int i = 0;
  byte data[8];
 
  GLCD.ClearScreen();

  //****************************** Draw the screen ********************************
  i = 0;
  textAreaSetting0.DefineArea(textShiftX, 1 + textShiftY * i , 31, 1 , System5x7);
  textAreaSetting0.ClearArea();
   textAreaSetting0.print("Exit");  
  GLCD.InvertRect(0, highlighthight * i, highlightwidth, highlighthight);

  i = 1;
  textAreaSetting1.DefineArea(textShiftX, 1 + textShiftY * i , 31, 1 , System5x7);
  textAreaSetting1.ClearArea();
  //textAreaSetting1.SetFontColor(PIXEL_OFF);
  StringSetting1 = "Clock: ";
  textAreaSetting1.print(StringSetting1);  

  i = 2;
  textAreaSetting2.DefineArea(textShiftX, 1 + textShiftY * i , 31, 1 , System5x7);
  textAreaSetting2.ClearArea();
  StringSetting2 = "Airswitch Min Speed: " + String(MinFlightSpeed,DEC) + " Kts";
  textAreaSetting2.print(StringSetting2);  

  i = 3;
  textAreaSetting3.DefineArea(textShiftX, 1 + textShiftY * i , 31, 1 , System5x7);
  textAreaSetting3.ClearArea();
  StringSetting3 = "AHRS Cal: 0";
  textAreaSetting3.print(StringSetting3);  
  


  //****************************** End of Draw the screen ********************************
  
  while (KeepLoop) {

   while (buttonState == LOW) { // button could have been held down at this point. wait fot release
       buttonState = digitalRead(Click_Button);
       delay(50);
  }

  // sowing time continuously

  DateTime now = RTC.now();
  year = now.year();
  month = now.month();
  dayOfMonth = now.day();
  hour = now.hour();
  minute = now.minute();
  second = now.second();

 

  if (secvalue != second) {
    StringSetting1 = "Clock: ";
    
    if (TimeConfig == 1) { // Check is the rightmost bit in the DisplayConfig set to 1. Is so it is LOC time otherwise UTC
      StringSetting1 += "LOC ";
    } else {
      StringSetting1 += "UTC ";
    }
    
    StringSetting1 += year;
    StringSetting1 += "-";
    if (month < 10) {
      StringSetting1 += "0";
    }
    StringSetting1 += month;
    StringSetting1 += "-";
    if (dayOfMonth < 10) {
      StringSetting1 += "0";
    }
    StringSetting1 += dayOfMonth;
    StringSetting1 += " ";
    if (hour < 10) {
      StringSetting1 += "0";
    }
      StringSetting1 += hour;
      StringSetting1 += ":";
    if (minute < 10) {
      StringSetting1 += "0";
    }
      StringSetting1 += minute;
      StringSetting1 += ":";  
      
    if (second < 10) {
      StringSetting1 += "0";
      
    }
      StringSetting1 += second;
    if (SettingItem == 1) {
      textAreaSetting1.SetFontColor(PIXEL_OFF);
    } else {
      textAreaSetting1.SetFontColor(PIXEL_ON);
    }
    textAreaSetting1.ClearArea();
    textAreaSetting1.print(StringSetting1);
    secvalue = second;
   
  }  

  //******************************************************** AHRS Calibration *****************
  // show AHRS calibration status continuously
  // show Save/Exit toggle
  // upon entry into the mode - disable the calibration refresh on the AHRS unit to avoid messing up calibration efforts
  //   refresh disabled by sending message id 35 with seccond bit set 1 (0x02)
  // If Save selected and button pressed - send a command to save the data (Message ID 35, first bit set 1)
  // If Exit selected and button pressed - just exit and send the command to re-enable the calibration refresh. The calibration data in EEPROM stays intact.

  // since we are outside of the mail loop we need to read the calibration data coming from CAN network
  if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&canId, &ext, &len, buf);
        if (canId == 73) {
          CalibrationStats = buf[6];
        }
    }
  
  if (CalibrationStats_old != CalibrationStats) {

     calSys = (0xC0 & CalibrationStats) >> 6;
     calGyro = (0x30 & CalibrationStats) >> 4;
     calAccel = (0x0C & CalibrationStats) >> 2;
     calMag = (0x03 & CalibrationStats) >> 0;  

     StringSetting3 = "AHRS Cal: ";
     StringSetting3 += "S:" + String(calSys) + " G:" + String(calGyro) + " A:" + String(calAccel) + " M:" + String(calMag);

    if (SettingItem == 3) {
      textAreaSetting3.SetFontColor(PIXEL_OFF);
    } else {
      textAreaSetting3.SetFontColor(PIXEL_ON);
    }
     textAreaSetting3.ClearArea();
     textAreaSetting3.print(StringSetting3);
     CalibrationStats_old = CalibrationStats;
  }

  //**************************************** end of showing current calibration data
  
  
  buttonState = digitalRead(Click_Button);
  if (buttonState == LOW and bTimer == 0 and MenuItem == 2) {
    bTimer = millis();
  }
 
  if (buttonState == HIGH and bTimer > 0 and MenuItem == 2) {
    ButtonPush = 1;
    bTimer = 0;
  }
  
  encCurrentValue = myEnc.read()/4;
  
  if (encCurrentValue != encLastValue) {
    GLCD.InvertRect(0, highlighthight * SettingItem, highlightwidth, highlighthight);
    SettingItem = (SettingItem + (encCurrentValue - encLastValue)) % MaxSettings;
    // due to weird implementation of MODULO function I had to do the follwoing line
    if (SettingItem <0) {
      SettingItem = MaxSettings + SettingItem;
    }
    GLCD.InvertRect(0, highlighthight * SettingItem, highlightwidth, highlighthight);
    encLastValue = encCurrentValue;

    ButtonPush = 0;

  } 

//******************************** Setting UTC/LOC time *************************
  if (SettingItem == 1 and ButtonPush == 1) {
    textAreaSetting1.ClearArea();
    textAreaSetting1.SetFontColor(PIXEL_ON);
    textAreaSetting1.print(StringSetting1);
    if (TimeSetPosition == 0) {
      GLCD.InvertRect(45+(TimeSetPosition*18), highlighthight+1, 20, highlighthight-2);
    } else {
      GLCD.InvertRect(64+(TimeSetPosition*18), highlighthight+1, 12, highlighthight-2);
    }
    while (KeepLoop1) {
      encCurrentValue = myEnc.read()/4;
  
      if (encCurrentValue != encLastValue) {
        if (TimeSetPosition == 0) {
          GLCD.InvertRect(45+(TimeSetPosition*18), highlighthight+1, 20, highlighthight-2);
        } else {
          GLCD.InvertRect(64+(TimeSetPosition*18), highlighthight+1, 12, highlighthight-2);
        }
        TimeSetPosition = (TimeSetPosition + (encCurrentValue - encLastValue)) % 6;
        // due to weird implementation of MODULO function I had to do the follwoing line
       if (TimeSetPosition <0) {
          TimeSetPosition = 6 + TimeSetPosition;
       }
        encLastValue = encCurrentValue;
        if (TimeSetPosition == 0) {
          GLCD.InvertRect(45+(TimeSetPosition*18), highlighthight+1, 20, highlighthight-2);
        } else {
          GLCD.InvertRect(64+(TimeSetPosition*18), highlighthight+1, 12, highlighthight-2);
        }
 
      }
      
      buttonState = digitalRead(Click_Button);
      if (buttonState == LOW) { // buttom pressed - need to hold the button to exit
        bTimer = millis();
        while (buttonState == LOW and millis() - bTimer < 1500) { // button released
           buttonState = digitalRead(Click_Button);
          delay(70);
        }
        if (buttonState == LOW and millis() - bTimer > 1500) { 
          KeepLoop1 = false;
        } else {

          switch (TimeSetPosition) {
             case 0:
               tmpValue = 0;
               tmpMinValue = 0;
               tmpMaxValue = 1;
               break;
             case 1:
               tmpValue = year - 2000;
               tmpMinValue = 19;
               tmpMaxValue = 99;
               break;
             case 2:
               tmpValue = month;
               tmpMinValue = 1;
               tmpMaxValue = 12;
               break;
             case 3:
               tmpValue = dayOfMonth;
               tmpMinValue = 1;
               tmpMaxValue = 31;
               break;
             case 4:
               tmpValue = hour;
               tmpMinValue = 0;
               tmpMaxValue = 23;
               break;
             case 5:
               tmpValue = minute;
               tmpMinValue = 0;
               tmpMaxValue = 59;
               break;
          }
          if (TimeSetPosition == 0) {
            GLCD.InvertRect(45+(TimeSetPosition*18), highlighthight-2, 20, highlighthight+3);
          } else {
            GLCD.InvertRect(63+(TimeSetPosition*18), highlighthight-2, 14, highlighthight+3);
          }
          encLastValue = myEnc.read()/4;
          while (KeepLoop2) {
            encCurrentValue = myEnc.read()/4;
            if (encCurrentValue != encLastValue) {
              tmpValue = tmpValue + (encCurrentValue - encLastValue);
              if (tmpValue > tmpMaxValue) {
                tmpValue = tmpMaxValue;
              }
              if (tmpValue < tmpMinValue) {
                tmpValue = tmpMinValue;
              }
              encLastValue = encCurrentValue;
              if (TimeSetPosition == 0) {
                GLCD.CursorToXY(46+(TimeSetPosition*18), highlighthight+1);
                if (tmpValue == 0) {
                  GLCD.Printf("UTC");
                } else {
                  GLCD.Printf("LOC");
                }
              } else {
                GLCD.CursorToXY(64+(TimeSetPosition*18), highlighthight+1);
                GLCD.Printf("%02d", tmpValue);
              }
            }  
            buttonState = digitalRead(Click_Button);
            if (buttonState == LOW) { // buttom pressed
              while (buttonState == LOW) { // button released
                buttonState = digitalRead(Click_Button);
                delay(50);
              }
              
              KeepLoop2 = false;
            }

        }
             // write the new value back into the correcponding valiable        
            switch (TimeSetPosition) {
                         case 0:
                           TimeConfig = tmpValue;
                           break;
                         case 1:
                           year = tmpValue + 2000;
                           break;
                         case 2:
                           month = tmpValue;
                           break;
                         case 3:
                           dayOfMonth = tmpValue;
                           break;
                         case 4:
                           hour = tmpValue;
                           break;
                         case 5:
                           minute = tmpValue;
                           break;
                      }
            if (TimeSetPosition == 0) {
              GLCD.InvertRect(45+(TimeSetPosition*18), highlighthight-2, 20, highlighthight+3);
            } else {
              GLCD.InvertRect(63+(TimeSetPosition*18), highlighthight-2, 14, highlighthight+3);
            }
            KeepLoop2 = true;
          
        }
      }
    }

    // set time here
    RTC.adjust(DateTime(year, month, dayOfMonth, hour, minute, 0));
    Serial.print("TimeConfig = ");
    Serial.println(TimeConfig);
    EEPROM.put(TimeConfig_MemOffset, TimeConfig);
    textAreaSetting1.SetFontColor(PIXEL_OFF);
    textAreaSetting1.ClearArea();
    textAreaSetting1.print(StringSetting1);
    bTimer = 0;
    ButtonPush = 0;
    KeepLoop1 = true;

    SendTime();      // broadcast the time immediately
    TimeMaster = 1;  // and become the time master
    TimeSendTimestamp = millis();
    Serial.println("The unit is set to a Time Master");
  }
//******************************** END of Setting UTC time *************************

   //***********************  Airswitch Min Speed setting  ***********************
  if (SettingItem == 2 and ButtonPush == 1) {
    // change string colour
    StringSetting2 = "Airswitch Min Speed: " + String(MinFlightSpeed,DEC) + " Kts";
    textAreaSetting2.ClearArea();
    textAreaSetting2.SetFontColor(PIXEL_ON);
    textAreaSetting2.print(StringSetting2);
    while (KeepLoop2) {
      encCurrentValue = myEnc.read()/4;
  
      if (encCurrentValue != encLastValue) {
  
        MinFlightSpeed = MinFlightSpeed + (encCurrentValue - encLastValue);
        encLastValue = encCurrentValue;
        StringSetting2 = "Airswitch Min Speed: " + String(MinFlightSpeed,DEC) + " Kts";
        textAreaSetting2.ClearArea();
        textAreaSetting2.print(StringSetting2);
        
      }
      buttonState = digitalRead(Click_Button);
      if (buttonState == LOW) { // buttom pressed
        while (buttonState == LOW) { // button released
           buttonState = digitalRead(Click_Button);
          delay(50);
        }
        KeepLoop2 = false;
      }
      
    }
    EEPROM.put(MinFlightSpeed_MemOffset, MinFlightSpeed);
    StringSetting2 = "Airswitch Min Speed: " + String(MinFlightSpeed,DEC) + " Kts";
    textAreaSetting2.SetFontColor(PIXEL_OFF);
    textAreaSetting2.ClearArea();
    textAreaSetting2.print(StringSetting2);
    ButtonPush = 0;
    KeepLoop2 = true;
  }
  
   //***********************  END of Airswitch Min Speed setting  ***********************


//***********************  AHRS calibration  ***********************

  if (SettingItem == 3 and ButtonPush == 1) {
    CalFlag = "N";
    
    Send_Calibration_Cammand(0x02);  

    StringSetting3 = "AHRS Cal: ";
    StringSetting3 += "S:" + String(calSys) + " G:" + String(calGyro) + " A:" + String(calAccel) + " M:" + String(calMag);
    
    StringSetting3 += " >Exit";

    textAreaSetting3.SetFontColor(PIXEL_ON);
    textAreaSetting3.ClearArea();
    textAreaSetting3.print(StringSetting3);
    
    while (KeepLoop3) {
       // since we are outside of the mail loop we need to read the calibration data coming from CAN network
        if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
        {
            CAN.readMsgBuf(&canId, &ext, &len, buf);
            if (canId == 73) {
              CalibrationStats = buf[6];
            }
            calSys = (0xC0 & CalibrationStats) >> 6;
            calGyro = (0x30 & CalibrationStats) >> 4;
            calAccel = (0x0C & CalibrationStats) >> 2;
            calMag = (0x03 & CalibrationStats) >> 0;  
        }

      
      encCurrentValue = myEnc.read()/4;

      StringSetting3 = "AHRS Cal: ";
      StringSetting3 += "S:" + String(calSys) + " G:" + String(calGyro) + " A:" + String(calAccel) + " M:" + String(calMag);

  
      if (encCurrentValue != encLastValue) { // there are only two possible values Y -save, N - ignore
        encLastValue = encCurrentValue;

        if (CalFlag == "Y") {
            CalFlag ="N";
           } else {
            CalFlag ="Y";
          }
        CalibrationStats_old = 255;
      }

      if (CalFlag == "Y") {
        StringSetting3 += " >Save";
      } else {
        StringSetting3 += " >Exit";
      }

      if (CalibrationStats_old != CalibrationStats) {
         textAreaSetting3.ClearArea();
         textAreaSetting3.print(StringSetting3);
         CalibrationStats_old = CalibrationStats;
      }

      buttonState = digitalRead(Click_Button);
      if (buttonState == LOW) { // buttom pressed
        while (buttonState == LOW) { // button released
           buttonState = digitalRead(Click_Button);
          delay(50);
        }
        KeepLoop3 = false;
      }
      
    }
        if (CalFlag == "Y") {
           Serial.println("###### sending command to save the data ######");
           Send_Calibration_Cammand(0x01);  // save the current calibration data into AHRS's EEPROM and resume calibration updates/resets
        } else {
           Send_Calibration_Cammand(0x00); // just resume calibration updates/resets
        }
        
        StringSetting3 = "AHRS Cal: ";
        StringSetting3 += "S:" + String(calSys) + " G:" + String(calGyro) + " A:" + String(calAccel) + " M:" + String(calMag) + "      ";
        
        
    textAreaSetting3.ClearArea();        
    textAreaSetting3.SetFontColor(PIXEL_OFF);
    textAreaSetting3.print(StringSetting3);
    ButtonPush = 0;
    KeepLoop3 = true;
  }

//*************************** End of BNO calibration ********************************


  if (SettingItem == 0 and ButtonPush == 1) {
    KeepLoop = false;
    MenuItem = 0;
  }

  }

 EFIS_Display();
}

void Send_Calibration_Cammand(byte CalCommand) {
  buf[0] = CalCommand;
  CAN.sendMsgBuf(35, 0, 1, buf); 
}
