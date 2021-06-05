void EFIS_Main() {
int encCurrentValue = 0;
String Tracking_TorM = "";
int TrackingNumber = 0;


  //************************************ Encoder *******************
  buttonState = digitalRead(Click_Button);
  
  if (buttonState == LOW and bTimer == 0 and MenuItem == 0) {
    bTimer = millis();
  }

  if (buttonState == HIGH and bTimer > 0 and MenuItem == 0) {
    bTimer = millis() - bTimer;
    if (bTimer < 2000) {
      encLastValue = myEnc.read()/4;
      GLCD.InvertRect(132, 30,57,9);
      MenuItem = 1;
    } 
    bTimer = 0;
  }

  if (buttonState == LOW and millis() - bTimer > 2000 and MenuItem == 0) {
    bTimer = 0;
    MenuItem = 2;
  }
  

if (MenuItem == 1) {
   setQNH();
}

if (MenuItem == 2) {
  EFIS_Menu();
}

//======================== change Middle screen ==========================
encCurrentValue = abs(myEnc.read()/4);

if (MidScreen != encCurrentValue % 3 and MenuItem == 0) {
  MidScreen = encCurrentValue % 3; // three screens for now: 0: Artificial Horizon; 1: GPS data; 2: TAS data  
  GLCD.FillRect(66, 1, 61, 50, PIXEL_OFF); // clear the area around the Horizon   
  if(MidScreen == 1) {
    Init_GPS();
    ForceDisplay = 1;
    Show_GPS(); 
  }
    if(MidScreen == 2) {
    Init_TAS();  
    ForceDisplay = 1;
    Show_TAS(); 
  }

}


// ========================= Main routine ======================================

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
    case 40:
      {
      // Airspeed, ALT, Vert speed
          Airspeed = (buf[1] << 8) | buf[0];
          Altitude  = (buf[4] << 16) | (buf[3] << 8) | buf[2];
          VertSpeed = (buf[6] << 8) | buf[5];
          Show_AData();
          if (MidScreen == 2) {
            Show_TAS();
          }
      }
      break;
    case 41:
      {
      //  AOA
          AOA = (buf[1] << 8) | buf[0];
          Show_AOA();
      }
      break;
    case 42:
      {
          OAT =  buf[0];
          Humidity  = buf[1];
         // Show_OAT();
      }
      break;
    case 43:
      {
          RawPressure = (buf[1] << 8) | buf[0];
      }
      break;
    case 72:
      {
        // HDG   Roll    Pitch   TurnRate  
          HDG = (buf[1] << 8) | buf[0];
          Roll  = (buf[3] << 8) | buf[2];
          Pitch = (buf[5] << 8) | buf[4];
          TurnRate = (buf[7] << 8) | buf[6];
          if (MidScreen == 0) {
              Show_Gyro();
          }
          Show_Heading();
      }
      break;
    case 73:
      {
       // AccX    AccY    AccZ    Calib 
          AccX = (buf[1] << 8) | buf[0];
          AccY  = (buf[3] << 8) | buf[2];
          AccZ = (buf[5] << 8) | buf[4];
          CalibrationStats = buf[6];

          Show_Accel();
      }
      break;
    case 100:
      {
       // GS    ALT   Track-T   Track-M -- 2 bytes each
          GroundSpeed = (buf[1] << 8) | buf[0];
          GPSaltitude  = (buf[3] << 8) | buf[2];
          TrackingTrue = (buf[5] << 8) | buf[4];
          TrackingMagnetic = (buf[7] << 8) | buf[6];
//          Serial.print("TrackingTrue: ");
//          Serial.println(TrackingTrue);
//          Serial.print("TrackingMagnetic: ");
//          Serial.println(TrackingMagnetic);
     
          if (TrackingTrue >= 0) {
            TrackingNumber = TrackingTrue;
            Tracking_TorM = "T";
          }
          if (TrackingMagnetic >= 0) {
            TrackingNumber = TrackingMagnetic;
            Tracking_TorM = "M";
          }

          if (TrackingNumber < 100) {
             Tracking = "0";
          }
          if (TrackingNumber < 10) {
             Tracking = Tracking + "0";
          }

          if (Tracking_TorM == "") {
            Tracking = "---";
          } else {
            Tracking = Tracking + TrackingNumber + " " + Tracking_TorM;
          }
          
          if (MidScreen == 1) {
              Show_GPS();
          }
          
      }
      break;

    default: 
      // if nothing else matches, do the default
      // default is optional
    break;
  }

        
} 
      
}
