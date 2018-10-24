void EGH_CHT() {

/* Data from J200
   CHT - 137,160,122,144,110,107
   EGT - 689, 677, 643, 660, 654, 635
   Cruise 2800rpm, 3500ft, 13 deg OAT, 119 TAS
*/
 
//************************* EGT **********************

DisplayEGT(1, 689);
DisplayEGT(2, 677);
DisplayEGT(3, 643);
DisplayEGT(4, 660);
DisplayEGT(5, 654);
DisplayEGT(6, 635);

DisplayCHT(1, 137);
DisplayCHT(2, 160);
DisplayCHT(3, 122);
DisplayCHT(4, 144);
DisplayCHT(5, 110);
DisplayCHT(6, 107);



}

/**********************************************  INIT EGT *******************************************/
void InitEGT(int CylNo) {
  
unsigned int TempLx = 90; //offset X for left Cyl temp
unsigned int TempLy = 3; //offset Y for left Cyl temp
unsigned int StepY = 9; // vertical Shift for each Cyl 
unsigned int StepX = 64; // horizontal Shift for each Cyl 

// this is "normal temperature tange
unsigned int TempMin = 600; //30% of the bottom scale
unsigned int TempMax = 750; //20% of the upper scale
unsigned int AbsMax;
unsigned int BarFull = 30; //full scale is 30 pix
unsigned int BarMin = 9; //lower range from zero to TempMin is 9 pix
unsigned int BarMax = 24; //upper range above TempMax is 6 pix
int BarLength = 0;
AbsMax = TempMax / 0.8;

 if (CylNo % 2 == 0) {
  GLCD.DrawRect(TempLx + 20 + 32,TempLy + (StepY * (CylNo-2)/2),30,8);
  GLCD.DrawVLine(TempLx + 52 + BarMin,TempLy + (StepY * (CylNo-2)/2),4);
  GLCD.DrawVLine(TempLx + 52 + BarMax,TempLy + (StepY * (CylNo-2)/2),4);
 } else {
  GLCD.DrawRect(TempLx + 20,TempLy + (StepY * (CylNo-1)/2),30,8);
  GLCD.DrawVLine(TempLx + 19 + BarFull - BarMin,TempLy + (StepY * (CylNo-1)/2),4);
  GLCD.DrawVLine(TempLx + 19 + BarFull - BarMax,TempLy + (StepY * (CylNo-1)/2),4);
 }



}

/*********************************************************************************************************/
/*********************************************************** Display EGT *********************************/

void DisplayEGT(int CylNo, int Temp) {

  /*
   * EGT Continuous Limits: 
   * EGT (Mid-Range / Cruise):    Min 680° - 720°C (1256° - 1328°F) 
   * EGT (Above 70% Power):    Min 640° - 680°C (1184° - 1256°F)
   */


   
unsigned int TempLx = 90; //offset X for left Cyl temp
unsigned int TempLy = 3; //offset Y for left Cyl temp
unsigned int StepY = 9; // vertical Shift for each Cyl 
unsigned int StepX = 64; // horizontal Shift for each Cyl 

// this is "normal temperature tange
unsigned int TempMin = 650; //30% of the bottom scale
unsigned int TempMax = 750; //20% of the upper scale
unsigned int AbsMax;
unsigned int BarFull = 30; //full scale is 30 pix
unsigned int BarMin = 9; //lower range from zero to TempMin is 9 pix
unsigned int BarMax = 24; //upper range above TempMax is 6 pix
int BarLength = 0;
String tmp_Temp = "";

AbsMax = TempMax / 0.8;

//bar length 
if (Temp <= TempMin) {
  BarLength = BarMin * Temp/TempMin;
} 

if (Temp > TempMin and Temp < TempMax) {
  BarLength = BarMin + (BarMax - BarMin) * (Temp - TempMin)/(TempMax - TempMin);
} 

if (Temp > TempMax) {
  BarLength = BarMax + (BarFull - BarMax) * (Temp - TempMax)/(AbsMax - TempMax);
} 

if (BarLength > AbsMax) {
  BarLength = AbsMax;
}

   GLCD.SelectFont(System5x7);
// GLCD.SelectFont(newbasic3x5);

 if (CylNo % 2 == 0) {
  GLCD.FillRect(TempLx + 53,TempLy + 2 + (StepY * (CylNo-2)/2),BarFull-2,4, WHITE); 
  GLCD.FillRect(TempLx + 53,TempLy + 2 + (StepY * (CylNo-2)/2),BarLength,4); 
  GLCD.DrawVLine(TempLx + 52 + BarMin,TempLy + (StepY * (CylNo-2)/2),4);
  GLCD.DrawVLine(TempLx + 52 + BarMax,TempLy + (StepY * (CylNo-2)/2),4);
  GLCD.CursorToXY(TempLx + 84, TempLy + (StepY * (CylNo-2)/2));
 } else {
  GLCD.FillRect(TempLx + 21 ,TempLy + 2 + (StepY * (CylNo-1)/2),BarFull-2,4, WHITE); 
  GLCD.FillRect(TempLx + 19 + BarFull - BarLength,TempLy + 2 + (StepY * (CylNo-1)/2),BarLength,4); 
  GLCD.DrawVLine(TempLx + 19 + BarFull - BarMin,TempLy + (StepY * (CylNo-1)/2),4);
  GLCD.DrawVLine(TempLx + 19 + BarFull - BarMax,TempLy + (StepY * (CylNo-1)/2),4);
  GLCD.CursorToXY(TempLx + 1, TempLy + (StepY * (CylNo-1)/2));
 }

  if (Temp<100) {
    tmp_Temp +=  " ";
  }
 if (Temp<10) {
    tmp_Temp +=  " ";
  }

  tmp_Temp +=  Temp;
  
  GLCD.print(tmp_Temp); 

}


//********************************************** Init CHT ************************************
void InitCHT(int CylNo) {
  
unsigned int TempLx = 90; //offset X for left Cyl temp
unsigned int TempLy = 36; //offset Y for left Cyl temp
unsigned int StepY = 9; // vertical Shift for each Cyl 
unsigned int StepX = 64; // horizontal Shift for each Cyl 

// this is "normal temperature tange
unsigned int TempMin = 90; //30% of the bottom scale
unsigned int TempMax = 200; //20% of the upper scale
unsigned int AbsMax;
unsigned int BarFull = 30; //full scale is 30 pix
unsigned int BarMin = 9; //lower range from zero to TempMin is 9 pix
unsigned int BarMax = 24; //upper range above TempMax is 6 pix
int BarLength = 0;
AbsMax = TempMax / 0.8;


 if (CylNo % 2 == 0) {
  GLCD.DrawRect(TempLx + 20 + 32,TempLy + (StepY * (CylNo-2)/2),30,8);
  GLCD.DrawVLine(TempLx + 52 + BarMin,TempLy + (StepY * (CylNo-2)/2),4);
  GLCD.DrawVLine(TempLx + 52 + BarMax,TempLy + (StepY * (CylNo-2)/2),4);
 } else {
  GLCD.DrawRect(TempLx + 20,TempLy + (StepY * (CylNo-1)/2),30,8);
  GLCD.DrawVLine(TempLx + 19 + BarFull - BarMin,TempLy + (StepY * (CylNo-1)/2),4);
  GLCD.DrawVLine(TempLx + 19 + BarFull - BarMax,TempLy + (StepY * (CylNo-1)/2),4);
 }

}  


/************************************************************************************************************/
/******************************************   Display CHT   *************************************************/

void DisplayCHT(int CylNo, int Temp) {

/*  From Jabiru docs
 * Max. CHT (Climb) 200°C  (392°F) 
 * Max Continuous CHT (Cruise) 180oC  (356oF)  
 * Notes:   
 * - Time with CHT at between 180°C and 200°C is not to exceed 5 Minutes 
 * - Time with engine speeds above 2850 RPM is not to exceed 10 minutes for    3300L models. 
 * - (Read Cylinder Head Temperature – CHT – under the spark plug nearest     to the exhaust on the hottest cylinder).  
 * 
 */

  
unsigned int TempLx = 90; //offset X for left Cyl temp
unsigned int TempLy = 36; //offset Y for left Cyl temp
unsigned int StepY = 9; // vertical Shift for each Cyl 
unsigned int StepX = 64; // horizontal Shift for each Cyl 

// this is "normal temperature tange
unsigned int TempMin = 90; //30% of the bottom scale
unsigned int TempMax = 200; //20% of the upper scale
unsigned int AbsMax;
unsigned int BarFull = 30; //full scale is 30 pix
unsigned int BarMin = 9; //lower range from zero to TempMin is 9 pix
unsigned int BarMax = 24; //upper range above TempMax is 6 pix
int BarLength = 0;
String tmp_Temp = "";
AbsMax = TempMax / 0.8;

//bar length 
if (Temp <= TempMin) {
  BarLength = BarMin * Temp/TempMin;
} 

if (Temp > TempMin and Temp < TempMax) {
  BarLength = BarMin + (BarMax - BarMin) * (Temp - TempMin)/(TempMax - TempMin);
} 

if (Temp > TempMax) {
  BarLength = BarMax + (BarFull - BarMax) * (Temp - TempMax)/(AbsMax - TempMax);
} 

if (BarLength > AbsMax) {
  BarLength = AbsMax;
}

GLCD.SelectFont(System5x7);

 if (CylNo % 2 == 0) {
  GLCD.DrawRect(TempLx + 20 + 32,TempLy + (StepY * (CylNo-2)/2),30,8);
  
  GLCD.FillRect(TempLx + 20 + 33,TempLy + 2 + (StepY * (CylNo-2)/2),BarFull-2,4, WHITE); 
  GLCD.FillRect(TempLx + 20 + 33,TempLy + 2 + (StepY * (CylNo-2)/2),BarLength,4); 
  GLCD.DrawVLine(TempLx + 52 + BarMin,TempLy + (StepY * (CylNo-2)/2),4);
  GLCD.DrawVLine(TempLx + 52 + BarMax,TempLy + (StepY * (CylNo-2)/2),4);
  GLCD.CursorToXY(TempLx +20 + 32 + 30 + 2, TempLy + (StepY * (CylNo-2)/2));
 } else {
  GLCD.DrawRect(TempLx + 20,TempLy + (StepY * (CylNo-1)/2),30,8);
  
  GLCD.FillRect(TempLx + 21,TempLy + 2 + (StepY * (CylNo-1)/2),BarFull-2,4,WHITE); 
  GLCD.FillRect(TempLx + 19 + BarFull - BarLength,TempLy + 2 + (StepY * (CylNo-1)/2),BarLength,4); 
  GLCD.DrawVLine(TempLx + 19 + BarFull - BarMin,TempLy + (StepY * (CylNo-1)/2),4);
  GLCD.DrawVLine(TempLx + 19 + BarFull - BarMax,TempLy + (StepY * (CylNo-1)/2),4);
  GLCD.CursorToXY(TempLx + 1, TempLy + (StepY * (CylNo-1)/2));
 }
 
 
 if (Temp<100) {
    tmp_Temp +=  " ";
  }

   if (Temp<10) {
    tmp_Temp +=  " ";
  }

  tmp_Temp +=  Temp;
  
  GLCD.print(tmp_Temp); 

}  

