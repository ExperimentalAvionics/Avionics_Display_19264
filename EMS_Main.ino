void EMS_Main() {
int encCurrentValue = 0;


  //************************************ EMS Encoder *******************
  buttonState = digitalRead(Click_Button);
  
  if (buttonState == LOW and bTimer == 0 and MenuItem == 0) {
    bTimer = millis();
  }

  if (buttonState == HIGH and bTimer > 0 and MenuItem == 0) {
    bTimer = millis() - bTimer;
    if (bTimer < 2000) {
      encLastValue = myEnc.read()/4;
      MenuItem = 1;
    } 
    bTimer = 0;
  }

  if (buttonState == LOW and millis() - bTimer > 2000 and MenuItem == 0) {
    bTimer = 0;
    MenuItem = 2;
  }
  

if (MenuItem == 1) {
   // Dont know yet
}

if (MenuItem == 2) {
  EMS_Menu();
}


// === Right half of the display can be changed to show various engine parameters
// === by default it is EGT/CHT screen
// ======================== Change Roght Half of the screen ==========================

encCurrentValue = abs(myEnc.read()/4);

if (RightScreen != encCurrentValue % 2 and MenuItem == 0) {
  RightScreen = encCurrentValue % 2; // two screens for now: 0: EGT+CHT; 1: OIL  
  GLCD.FillRect(83, 0, 111, 63, PIXEL_OFF); // clear the area around the Horizon   
  if(RightScreen == 1) {
    Init_EngineAltData1();
  }
  if(RightScreen == 0) {
    RightScreenDefault();
    textBatVoltLabel.print("BAT:     V   C");
    Show_BAT();
  }
}



    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
     //   Serial.print("Msg wait: ");
     //   Serial.println(millis() - LoopTimer);
        
        LoopTimer = millis();
        
        CAN.readMsgBuf(&canId, &ext, &len, buf);    // read data,  len: data length, buf: data buf

        // canId = CAN.getCanId();


switch (canId) {

      case 25:
      {
          // another unit sending time and requesting to become a time master
          ReceiveTime();
      }
      break;
    case 46:    // Received QNH from another unit. It can arrive when unit is in EMS mode
      {
          QNH = (buf[1] << 8) | buf[0];
          EEPROM.put(QNH_MemOffset, QNH);
      }
      break;
    case 50:
      {
      //RPM, Fuel Flow and Fuel Pressure
          RPM          = (buf[1] << 8) | buf[0];
          FuelPressure     = (buf[3] << 8) | buf[2];
          FuelFlow = (buf[5] << 8) | buf[4];
          
          Show_RPM();
          Show_FuelFlow();
          Show_FuelPressure();
      }
      break;
      
    case 80:
      {
      //******* Fuel tanks level
          TankLevel1 = (buf[1] << 8) | buf[0];
      //  TankLevel2 = (buf[3] << 8) | buf[2];  // if you have two fuel tanks
          
          Show_FuelLevel();
      }
      break;

    case 81:
      {
      //******* Oil temp and pressure
          OilPressure       = (buf[1] << 8) | buf[0];
          OilTemperature    = (buf[3] << 8) | buf[2];

          Show_Oil();
      }
      break;

    case 82:
      {
      //******* EGT and CHT 1 and 2
          EGT[1] = (buf[1] << 8) | buf[0];
          EGT[2] = (buf[3] << 8) | buf[2];
          CHT[1] = (buf[5] << 8) | buf[4];
          CHT[2] = (buf[7] << 8) | buf[6];

          if (RightScreen == 0) {
          
            DisplayEGT(1, EGT[1]);
            DisplayEGT(2, EGT[2]);
  
            DisplayCHT(1, CHT[1]);
            DisplayCHT(2, CHT[2]);
          }

      }
      break;

    case 83:
      {
      //******* EGT and CHT 3 and 4
          EGT[3] = (buf[1] << 8) | buf[0];
          EGT[4] = (buf[3] << 8) | buf[2];
          CHT[3] = (buf[5] << 8) | buf[4];
          CHT[4] = (buf[7] << 8) | buf[6];

          if (RightScreen == 0) {
            DisplayEGT(3, EGT[3]);
            DisplayEGT(4, EGT[4]);
  
            DisplayCHT(3, CHT[3]);
            DisplayCHT(4, CHT[4]);
          }
      }
      break;

    case 84:
      {
      //******* EGT and CHT 5 and 6
          EGT[5] = (buf[1] << 8) | buf[0];
          EGT[6] = (buf[3] << 8) | buf[2];
          CHT[5] = (buf[5] << 8) | buf[4];
          CHT[6] = (buf[7] << 8) | buf[6];

          if (RightScreen == 0) {
            DisplayEGT(5, EGT[5]);
            DisplayEGT(6, EGT[6]);
  
            DisplayCHT(5, CHT[5]);
            DisplayCHT(6, CHT[6]);
          }
      }
      break;

    case 85:
      {
      //******* Electric system Volts and Amps
          EL_Volts = (buf[1] << 8) | buf[0];
          EL_AltAmps  = (buf[3] << 8) | buf[2]; // Alternator Amps
          EL_BatAmps  = (buf[5] << 8) | buf[4]; // Battery Amps

          Show_VoltAmp();
      }
      break;

    case 86:
      {
       //******* Backup Battery Voltage and Status
          BAT_Volts = (buf[1] << 8) | buf[0];
          BAT_Status  =  buf[2]; 
          BAT_Temperature  = buf[3];
          if (RightScreen == 0) {
            Show_BAT();
          }
      }
      break;

    case 112:
      {
 //       Serial.print(" Data: ");
 //       for(int i = 0; i<8; i++)    // print the data
 //       {
 //           Serial.print(buf[i]);
 //           Serial.print("\t");
 //        }
 //        Serial.println("");
      //******* Engine total time
            TT_RPM   = ((unsigned long)buf[3] << 24) | ((unsigned long)buf[2] << 16) | ((unsigned long)buf[1] << 8) | (unsigned long)buf[0];
            TT_Clock = ((unsigned long)buf[7] << 24) | ((unsigned long)buf[6] << 16) | ((unsigned long)buf[5] << 8) | (unsigned long)buf[4];

//     Serial.print("TT_RPM: ");
//     Serial.println(TT_RPM);

//     Serial.print("TT_Clock: ");
//     Serial.println(TT_Clock);
  
          Show_TT();
      }
      break;

    default: 
      // if nothing else matches, do the default
      // default is optional
    break;
  }

      if (RightScreen == 1) {
          EngineAltData1();
      }
    
    } 
}
