void Show_Heading() {

  if (CalibrationStats != CalibrationStats_old or ForceDisplay == 1) {
    CalibrationStats_old = CalibrationStats;
    textAreaMagCal.ClearArea();
    textAreaMagCal.Printf("%01d", (0x03 & CalibrationStats));
  }
  if (HDG != HDG_old or ForceDisplay == 1) {
    HDG_old = HDG;
    textAreaMAG.ClearArea();
    textAreaMAG.Printf("%03d", HDG);
  }
  ForceDisplay = 0; 
}

void Show_Gyro() {
  int  gRoll, gPitch, yStart, yEnd, xStart, xEnd, xZero = 96, yZero = 26;
  int yBug, xBug;  
  int xm60, ym60;
  int xm30, ym30;
  int xp60, yp60;
  int xp30, yp30;
  String s_tmp;
  float Gforce = 1.0;
  int iGforce;


  // Check calibration status of the sensors
/*
  uint8_t calstat = readByte(0x29, Adafruit_BNO055::BNO055_CALIB_STAT_ADDR);
  Serial.println("Not calibrated = 0, fully calibrated = 3");
  Serial.print("System calibration status "); Serial.println( (0xC0 & calstat) >> 6);
  Serial.print("Gyro   calibration status "); Serial.println( (0x30 & calstat) >> 4);
  Serial.print("Accel  calibration status "); Serial.println( (0x0C & calstat) >> 2);
  Serial.print("Mag    calibration status "); Serial.println( (0x03 & calstat) >> 0);
*/
  /*
  bno.setMode(Adafruit_BNO055::OPERATION_MODE_CONFIG);
  Serial.println(bno.getCalvalMOXL());
  Serial.println(bno.getCalvalMOXM());
  Serial.println(bno.getCalvalMOYL());
  Serial.println(bno.getCalvalMOYM());
  Serial.println(bno.getCalvalMOZL());
  Serial.println(bno.getCalvalMOZM());
  bno.setMode(Adafruit_BNO055::OPERATION_MODE_NDOF);
  */

  // set the local variables
  gRoll = (-1) * Roll;  // This (-1) is here due to legacy code. Needs to be cleaned up later down below
  gPitch = (-1) * Pitch;
  
  
  if (abs(gPitch)>90) {
    if (gRoll > 0 ) {
      gRoll = 180-gRoll;
    } else {
      gRoll = -180-gRoll;
    }
  }

  if (gPitch>90) {
    gPitch = 180 - gPitch;
  }

  if (gPitch<-90) {
    gPitch = -180 - gPitch;
  }



  s_tmp = "";
  if (abs(gRoll)<10) {
    s_tmp += " ";  
  }
    
  s_tmp += abs(gRoll);
  
  if (gRoll<0) {  
    s_tmp += "R";  
  }
  if (gRoll>0) {  
    s_tmp += "L";  
  }

  textAreaBottomL.ClearArea();
  textAreaBottomL.print(s_tmp);
  
  s_tmp = "";
  if (abs(gPitch)<10) {
    s_tmp += " ";  
  }
    
  s_tmp += abs(gPitch);
  
  if (gPitch<0) {  
    s_tmp += "U";  
  }
  if (gPitch>0) {  
    s_tmp += "D";  
  }

  textAreaBottomR.ClearArea();
  textAreaBottomR.print(s_tmp); 

  //top marker
  GLCD.DrawLine(xZero, 5, xZero, 5);
  GLCD.DrawLine(xZero-1, 6, xZero+1, 6);
  GLCD.DrawLine(xZero-2, 7, xZero+2, 7);
  //GLCD.DrawLine(xZero, 1, xZero, 2);
  
  //left and right markers
  //Left
  GLCD.DrawLine(66,yZero-2, 66, yZero+2);
  GLCD.DrawLine(67,yZero-1, 67, yZero+1);
  GLCD.DrawLine(68,yZero, 68, yZero);
  //Right
  GLCD.DrawLine(126,yZero-2, 126, yZero+2);
  GLCD.DrawLine(125,yZero-1, 125, yZero+1);
  GLCD.DrawLine(124,yZero, 124, yZero);

  // Plane picture
  //tail
  GLCD.DrawLine(xZero-18, yZero, xZero+18, yZero);
  // wings
  GLCD.DrawLine(xZero, 12, xZero, 20);
  // body
  GLCD.DrawCircle(xZero, yZero, 5); 
  GLCD.DrawLine(xZero, yZero, xZero, yZero, PIXEL_OFF);


 //Arc Bug
  xBug = xZero + (yZero)*sin(3.14*gRoll/180);
 if (abs(gRoll)<90) {
   yBug = yZero-(yZero)*cos(3.14*gRoll/180);
 } else {
   yBug = yZero-(yZero-12)*cos(3.14*gRoll/180);
 }
 
 GLCD.DrawRect(xBugOld-1, yBugOld+1,3,3, PIXEL_OFF);
 GLCD.DrawRect(xBug-1, yBug+1,3,3);
 xBugOld = xBug;
 yBugOld = yBug;

// marker -60
  xm60 = xZero + (yZero)*sin(3.14*(gRoll-60)/180);
if (abs(gRoll-60)<90) {
  ym60 =  yZero-(yZero)*cos(3.14*(gRoll-60)/180);
} else {
  ym60 =  yZero-(yZero-11)*cos(3.14*(gRoll-60)/180);
}

GLCD.DrawRect(xm60_old, ym60_old+1, 2, 2, PIXEL_OFF);
GLCD.DrawRect(xm60, ym60+1, 2, 2);

xm60_old = xm60;
ym60_old = ym60;

// end of marker -60

// marker -30

xm30 = xZero + (yZero-1)*sin(3.14*(gRoll-30)/180);
if (abs(gRoll-30)<90) {
  ym30 = yZero-(yZero-1)*cos(3.14*(gRoll-30)/180);
} else {
  ym30 = yZero-(yZero-1-11)*cos(3.14*(gRoll-30)/180);
}
GLCD.DrawRect(xm30_old, ym30_old+1, 2, 2, PIXEL_OFF);
GLCD.DrawRect(xm30, ym30+1, 2, 2);

xm30_old = xm30;
ym30_old = ym30;

// end of marker -30

// marker +60

xp60 = xZero + (yZero)*sin(3.14*(gRoll+60)/180);
if (abs(gRoll+60)<90) {
  yp60 =  yZero-(yZero)*cos(3.14*(gRoll+60)/180);
} else {
  yp60 =  yZero-(yZero-11)*cos(3.14*(gRoll+60)/180);
}
GLCD.DrawRect(xp60_old, yp60_old+1, 2, 2, PIXEL_OFF);
GLCD.DrawRect(xp60, yp60+1, 2, 2);

xp60_old = xp60;
yp60_old = yp60;

// end of marker +60

// marker +30

xp30 = xZero + (yZero-1)*sin(3.14*(gRoll+30)/180);
if (abs(gRoll+30)<90) {
  yp30 = yZero-(yZero-1)*cos(3.14*(gRoll+30)/180);
} else {
  yp30 = yZero-(yZero-1-11)*cos(3.14*(gRoll+30)/180);
}
GLCD.DrawRect(xp30_old, yp30_old+1, 2, 2, PIXEL_OFF);
GLCD.DrawRect(xp30, yp30+1, 2, 2);

xp30_old = xp30;
yp30_old = yp30;

// end of marker +30




// draw the horizon line
  xStart = 66;
  xEnd = 126;
  if (abs(gRoll) < 90) {
    yStart = yZero - 30*tan(3.14*gRoll/180) - yZero*sin(3.14*gPitch/180);
    yEnd = yZero + 30*tan(3.14*gRoll/180) - yZero*sin(3.14*gPitch/180);
  } else {
    yStart = yZero - 30*tan(3.14*gRoll/180) + yZero*sin(3.14*gPitch/180);
    yEnd = yZero + 30*tan(3.14*gRoll/180) + yZero*sin(3.14*gPitch/180);
  }

  if (yStart < 1 ) {    
    xStart = xStart + (1-yStart)/tan(3.14*gRoll/180);
    yStart = 1;
  }

  if (yStart > 42 ) {
    xStart = xStart + (42-yStart)/tan(3.14*gRoll/180);
    yStart = 42;
  }

  if (yEnd < 1) {
    xEnd = xEnd + (1-yEnd)/tan(3.14*gRoll/180);
    yEnd = 1;
  }

  if (yEnd > 42) {
    xEnd = xEnd + (42-yEnd)/tan(3.14*gRoll/180);
    yEnd = 42;
  }


  GLCD.DrawLine(xStartOld, yStartOld, xEndOld, yEndOld,PIXEL_OFF);
  GLCD.DrawLine(xStart, yStart, xEnd, yEnd);

// end of horizon line
  
  xStartOld = xStart;
  yStartOld = yStart;
  xEndOld = xEnd;
  yEndOld = yEnd;

// ****************** G-Force meter ******************************

    Gforce = (float)AccZ/100;
    
    iGforce = round(Gforce*10/9.8);
   
    textAreaGmeter.ClearArea();
    textAreaGmeter.print("G");
    textAreaGmeter.CursorTo(2);
    textAreaGmeter.println(iGforce/10.0, 1); 

}


//***********************************************************************************************
void Show_Accel() {
int xBall, xZero = 96;
float ball;
    
//************************ Slip ball **************************


  ball = ((float)AccX/100) * 4.0; // convert to number of pixels and set sensitivity

 // set max deflection
 
  if (ball > 26) {
    ball = 26;
  }
  if (ball < -26) {
    ball = -26;
  }

  xBall = xZero - ball;

if (xBallOld != xBall or ForceDisplay == 1) {
  
    GLCD.FillCircle(xBallOld, 58, 3, PIXEL_OFF); 
    GLCD.FillCircle(xBall, 58, 3); 
    xBallOld = xBall;
    
    //GLCD.DrawVLine(96, 53, 10);
    GLCD.DrawVLine(91, 53, 10);
    GLCD.DrawVLine(101, 53, 10); 

}
    ForceDisplay = 0;
// ************************** END OF Slipball stuff *******************************


  
}
