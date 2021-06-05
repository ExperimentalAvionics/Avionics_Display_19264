void Show_AData() {

if (Airspeed <10 ) {
  Airspeed = 0; 
 }

// only refresh the figure when it changes to reduce flicker

  if (Airspeed != Airspeed_old or ForceDisplay == 1) {
    Airspeed_old = Airspeed;
    textAreaSPEED.ClearArea();
    textAreaSPEED.Printf("%03d", Airspeed); 
  }

//====== Altitude Display =========
//== Altitude figure on display will change only if it is different from prevous value by 5ft or more 
//== the reason is to stabilize display and avoid unnecessary flickering of the numbers

  if (abs(Altitude_old - Altitude)>5 or ForceDisplay == 1) {
    Altitude_old = Altitude;
    textAreaALT.ClearArea();
    textAreaALT.Printf("%05d", Altitude_old); //Altitude in ft
  }

//====== VSI Display =========
//== VSI figure on display will change only if it is different from prevous value by 20 ft/min or more
//== If VSI is within +/- 70ft/min the VSI will display Zero 
//== the reason is to stabilize display and avoid unnecessary flickering of the numbers

  if (abs(VertSpeed_old - VertSpeed) > 20 or ForceDisplay == 1) {

    VertSpeed_old = VertSpeed;
    if (abs(VertSpeed_old)<70) {
      VertSpeed_old = 0;
    }
    textAreaVSIvalue.ClearArea();
    textAreaVSIvalue.Printf("%4d", abs(VertSpeed_old)); 
  
    textAreaVSIarrow.ClearArea();
  
    if (VertSpeed_old > 0) {
      textAreaVSIarrow.print("%"); // going UP
    }
  
    if (VertSpeed_old < 0) {
      textAreaVSIarrow.print("&"); // going DOWN
    }
  }

  ForceDisplay = 0;
}

void Show_AOA() {
byte val;
// Send AoA information to the LED display via I2C (address = x09)
// AOA is int, so we need to send two bytes
 
  Wire.beginTransmission(9); // transmit to device x09
  val = AOA >> 8;
  Wire.write(val);           // sends AOA 
  val = AOA;
  Wire.write(val);           // sends AOA 
  Wire.endTransmission();    // stop transmitting
    
}

void Init_TAS() {
// prepare static stuff on the screen
    textAreaTASDATA.print("TRUE AIRSPEED");
    textAreaOATvalue.ClearArea();
    textAreaTASvalue.ClearArea();
    textAreaWNDdirection.ClearArea();
    textAreaWNDspeed.ClearArea();
    textAreaOAT.print("OAT:");
    textAreaTAS.print("TAS:");
    textAreaWND.print("WND:");
//    textAreaOATvalue.print(0);   
//    textAreaTASvalue.print(0); 
//    textAreaWNDdirection.print(0); 
//    textAreaWNDspeed.print(0);
}


void Show_TAS() {
  // display TAS, OAT and Wind
  // a bit of approximation for TAS. Good enough fopr practical purposes
  
  Delta = 288.15/((float)OAT/10.0 + 273.15)*((float)RawPressure/10132.5); //note RawPressure is hPa * 10
  
  if (Delta > 0) {        // just in case some sensor data goes mad
    TAS = round(Airspeed/sqrt(Delta));
  } else {
    TAS = 0;
  }
  
  if (TAS != TAS_old or ForceDisplay == 1) {
    TAS_old = TAS;
    textAreaTASvalue.ClearArea();
    textAreaTASvalue.print(TAS);   
  }
  
  if (OAT != OAT_old or ForceDisplay == 1) {
    OAT_old = OAT;
    textAreaOATvalue.ClearArea();
    textAreaOATvalue.print(OAT_old/10); 
  }

    ForceDisplay = 0;
}
