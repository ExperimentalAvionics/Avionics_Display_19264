void EFIS_Menu() {
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
 byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
 int secvalue = 0;
 int TimeSetPosition = 0;

 int CalCurrValue = 0;
 String CalDataCurrentString =""; // current calibration data
 String CalDataNewString =""; // temporary storage for current (latest) calibration data
 String CalFlag = "Y";

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
  textAreaSetting0.DefineArea(textShiftX, 1 + textShiftY * i , 29, 1 , System5x7);
  textAreaSetting0.ClearArea();
   textAreaSetting0.print("Exit");  
  GLCD.InvertRect(0, highlighthight * i, highlightwidth, highlighthight);

  i = 1;
  textAreaSetting1.DefineArea(textShiftX, 1 + textShiftY * i , 29, 1 , System5x7);
  textAreaSetting1.ClearArea();
  //textAreaSetting1.SetFontColor(PIXEL_OFF);
  StringSetting1 = "Clock: ";
  textAreaSetting1.print(StringSetting1);  

  i = 2;
  textAreaSetting2.DefineArea(textShiftX, 1 + textShiftY * i , 29, 1 , System5x7);
  textAreaSetting2.ClearArea();
  StringSetting2 = "Airswitch Min Speed: " + String(MinFlightSpeed,DEC) + " Kts";
  textAreaSetting2.print(StringSetting2);  

  i = 3;
  textAreaSetting3.DefineArea(textShiftX, 1 + textShiftY * i , 31, 1 , System5x7);
  textAreaSetting3.ClearArea();
  StringSetting3 = "Mag/Cal Q:0";
  textAreaSetting3.print(StringSetting3);  
  


  //****************************** End of Draw the screen ********************************
  
  while (KeepLoop) {

   while (buttonState == LOW) { // button could have been held down at this point. wait fot release
       buttonState = digitalRead(Click_Button);
       delay(50);
  }

  // sowing time constantly
//  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

  DateTime now = RTC.now();
  year = now.year();
  month = now.month();
  dayOfMonth = now.day();
  hour = now.hour();
  minute = now.minute();
  second = now.second();

  if (secvalue != second) {
    StringSetting1 = "Clock: 20";
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

  //******************************************************** Mag Calibration *****************
  // show magnetometer calibration data continuously
  // show Yes/No toggle
  // if Yes selected - show new calibration data
  // if No selected, show old calibration data from EEPROM (not the data before calibration. Calibration data changes all the time!!!!)
  // If Yes selected and button pressed - write data into EEPROM
  // If No selected and button pressed - do nothing, just exist. The calibration data in EEPROM stays intact.
  // current calibration doesnt change regardsless of the settings
  // this is to store calibration data just for startup.
  // dont let calibration to be saved if quality is less than 3
  
  CalibrationStats = 0; // bno.getCalib();

//  bno.setMode(Adafruit_BNO055::OPERATION_MODE_CONFIG);
//  delay(50);

//  readBytes(BNO055_ADDRESS, Adafruit_BNO055::MAG_OFFSET_X_LSB_ADDR, 6, &data[0]);
//  CalDataNewString = String(data[0], HEX) + ":" + String(data[1], HEX) + ":" + String(data[2], HEX) + ":" + String(data[3], HEX) + ":" + String(data[4], HEX) + ":" + String(data[5], HEX);
  
//  data[0] = bno.getCalvalMRL();                 // Read Magnetic calibration values
//  data[1] = bno.getCalvalMRM();
//  data[2] = bno.getCalvalMOXL();
//  data[3] = bno.getCalvalMOXM();
//  data[4] = bno.getCalvalMOYL();
//  data[5] = bno.getCalvalMOYM();
//  data[6] = bno.getCalvalMOZL();
//  data[7] = bno.getCalvalMOZM();

//  CalDataNewString = String(data[2], HEX) + ":" + String(data[3], HEX) + ":" + String(data[4], HEX) + ":" + String(data[5], HEX) + ":" + String(data[6], HEX) + ":" + String(data[7], HEX); // display calibration balues all except radius
  
//  bno.setMode(Adafruit_BNO055::OPERATION_MODE_NDOF);
//  delay(50);

  if ((CalibrationStats != (0x03 & CalibrationStats)) || (CalDataNewString != CalDataCurrentString)) {   // check if calibration quality value changed

     CalCurrValue = (0x03 & CalibrationStats);
     StringSetting3 = "Mag/Cal Q:";
     StringSetting3 += CalCurrValue;

     CalDataCurrentString = CalDataNewString;
     StringSetting3 += "   ";
     StringSetting3 += CalDataCurrentString;
     
     textAreaSetting3.ClearArea();
     textAreaSetting3.print(StringSetting3);
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

//******************************** Setting UTC time *************************
  if (SettingItem == 1 and ButtonPush == 1) {
    textAreaSetting1.ClearArea();
    textAreaSetting1.SetFontColor(PIXEL_ON);
    textAreaSetting1.print(StringSetting1);
    GLCD.InvertRect(58+(TimeSetPosition*18), highlighthight+1, 12, highlighthight-2);
    while (KeepLoop1) {
      encCurrentValue = myEnc.read()/4;
  
      if (encCurrentValue != encLastValue) {
        GLCD.InvertRect(58+(TimeSetPosition*18), highlighthight+1, 12, highlighthight-2);
        TimeSetPosition = (TimeSetPosition - (encCurrentValue - encLastValue)) % 5;
        // due to weird implementation of MODULO function I had to do the follwoing line
       if (TimeSetPosition <0) {
          TimeSetPosition = 5 + TimeSetPosition;
       }
        encLastValue = encCurrentValue;
        GLCD.InvertRect(58+(TimeSetPosition*18), highlighthight+1, 12, highlighthight-2);
 
      }
      
      buttonState = digitalRead(Click_Button);
      if (buttonState == LOW) { // buttom pressed - need to hold the button to exit
        bTimer = millis();
        while (buttonState == LOW and millis() - bTimer < 1500) { // button released
           buttonState = digitalRead(Click_Button);
          delay(50);
        }
        if (millis() - bTimer > 1500) { 
          KeepLoop1 = false;
        } else {

          switch (TimeSetPosition) {
             case 0:
               tmpValue = year;
               tmpMinValue = 15;
               tmpMaxValue = 99;
               break;
             case 1:
               tmpValue = month;
               tmpMinValue = 1;
               tmpMaxValue = 12;
               break;
             case 2:
               tmpValue = dayOfMonth;
               tmpMinValue = 1;
               tmpMaxValue = 31;
               break;
             case 3:
               tmpValue = hour;
               tmpMinValue = 0;
               tmpMaxValue = 23;
               break;
             case 4:
               tmpValue = minute;
               tmpMinValue = 0;
               tmpMaxValue = 59;
               break;
          }
          
          GLCD.InvertRect(57+(TimeSetPosition*18), highlighthight-2, 14, highlighthight+3);
          while (KeepLoop2) {
            encCurrentValue = myEnc.read()/4;
            if (encCurrentValue != encLastValue) {
              tmpValue = tmpValue - (encCurrentValue - encLastValue);
              if (tmpValue > tmpMaxValue) {
                tmpValue = tmpMaxValue;
              }
              if (tmpValue < tmpMinValue) {
                tmpValue = tmpMinValue;
              }
              encLastValue = encCurrentValue;
              GLCD.CursorToXY(58+(TimeSetPosition*18), highlighthight+1);
              GLCD.Printf("%02d", tmpValue);
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
                           year = tmpValue;
                           break;
                         case 1:
                           month = tmpValue;
                           break;
                         case 2:
                           dayOfMonth = tmpValue;
                           break;
                         case 3:
                           hour = tmpValue;
                           break;
                         case 4:
                           minute = tmpValue;
                           break;
                      }          
            GLCD.InvertRect(57+(TimeSetPosition*18), highlighthight-2, 14, highlighthight+3);
            KeepLoop2 = true;
          
        }
      }
    }

    // set time here
    //setDS3231time(00,minute,hour,7,dayOfMonth,month,year);
    
    textAreaSetting1.SetFontColor(PIXEL_OFF);
    textAreaSetting1.ClearArea();
    textAreaSetting1.print(StringSetting1);
    bTimer = 0;
    ButtonPush = 0;
    KeepLoop1 = true;

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


//***********************  BNO Magnetometer calibration  ***********************
/*
  if (SettingItem == 3 and ButtonPush == 1) {
    CalFlag = "Y";
    StringSetting3 = "Mag/Cal Q:";
    StringSetting3 += CalCurrValue;
    StringSetting3 += " Y ";
    StringSetting3 += CalDataCurrentString;
    textAreaSetting3.ClearArea();
    textAreaSetting3.print(StringSetting3);
    
    while (KeepLoop3) {
      encCurrentValue = myEnc.read()/4;
  
      if (encCurrentValue != encLastValue) { // there are only two possible values Y -save, N - ignore
        encLastValue = encCurrentValue;

        StringSetting3 = "Mag/Cal Q:";
        StringSetting3 += CalCurrValue;

      if (CalFlag == "Y") {
          CalFlag ="N";
        StringSetting3 += " N ";
        StringSetting3 += CalDataOldString;
        } else {
          CalFlag ="Y";
        StringSetting3 += " Y ";
        StringSetting3 += CalDataCurrentString;
        }
  
        textAreaSetting3.ClearArea();
        textAreaSetting3.print(StringSetting3);
        
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
           for (z=0;z<8;z++) {
             EEPROM.put(BNO_MemOffset + z, byte(data[z]));
           }
        }
        StringSetting3 = "Mag/Cal Q:";
        StringSetting3 += CalCurrValue;
        StringSetting3 += "   ";
        StringSetting3 += CalDataCurrentString;
        
    textAreaSetting3.SetFontColor(PIXEL_OFF);
    textAreaSetting3.ClearArea();
    textAreaSetting3.print(StringSetting3);
    ButtonPush = 0;
    KeepLoop3 = true;
  }
*/
//*************************** End of BNO calibration ********************************


  if (SettingItem == 0 and ButtonPush == 1) {
    KeepLoop = false;
    MenuItem = 0;
  }

  }

 EFIS_Display();
}

/*
void SetMinFlightSpeed() {
int encCurrentValue = 0;

encCurrentValue = myEnc.read()/4;

if (encCurrentValue != encLastValue) {

   MinFlightSpeed = MinFlightSpeed + (encCurrentValue - encLastValue);
   encLastValue = encCurrentValue;

}
   

  
}

*/
