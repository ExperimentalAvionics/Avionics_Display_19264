void Show_Oil() {

/* Jabiru docs say
 *  Oil Pressure 
 *  – Normal Operations Min  220 kPa  (31 psi) Max  525 kPa  (76 psi) 
 *  – Idle Min 80 kPa  (11 psi) – Starting & Warm up Max 525 kPa  (76 psi) 
 *  Oil Temperature: Min 15°C  (59°F) Max. 118 oC  (244°F) 
 *  Oil  Continuous Temperature 80 - 100°C  (176° - 212°F) 
 */



// this is normal oil temperature range
unsigned int TempMin = 80; //30% of the bottom scale
unsigned int TempMax = 100; //20% of the upper scale

unsigned int PressMin = 80; //kPa
unsigned int PressMax = 525; //kPa

unsigned int AbsMax;
unsigned int BarFull = 45; //full scale is 45 pix
unsigned int BarMin = 11; //lower range from zero to TempMin is 11 pix
unsigned int BarMax = 21; //upper range above TempMax is 6 pix
int BarLength = 0;
AbsMax = TempMax / 0.8;

//bar length 
if (OilTemperature <= TempMin) {
  BarLength = (float)BarMin * (float)OilTemperature/(float)TempMin;
} 

if (OilTemperature > TempMin and OilTemperature < TempMax) {
  BarLength = BarMin + (BarMax - BarMin) * (OilTemperature - TempMin)/(TempMax - TempMin);
} 

if (OilTemperature > TempMax) {
  BarLength = BarMax + (BarFull - BarMax) * (OilTemperature - TempMax)/(AbsMax - TempMax);
} 

if (BarLength > BarFull) {
  BarLength = BarFull;
}


//   GLCD.DrawRect(35,43,46,11);

   GLCD.FillRect(36,49,BarFull-1,3, WHITE);
   GLCD.FillRect(36,49,BarLength,3);
   GLCD.DrawLine(47, 52, 47, 50); // Green Temp Min   
   GLCD.DrawLine(67, 52, 67, 50); // Green Temo Max   


// markers

/* 
 *  Pressure
 */

AbsMax = PressMax / 0.8;

//bar length 
if (OilPressure <= PressMin) {
  BarLength = (float)BarMin * (float)OilPressure/(float)PressMin;
} 

if (OilPressure > PressMin and OilPressure < PressMax) {
  BarLength = BarMin + (BarMax - BarMin) * (OilPressure - PressMin)/(PressMax - PressMin);
} 

if (OilPressure > PressMax) {
  BarLength = BarMax + (BarFull - BarMax) * (OilPressure - PressMax)/(AbsMax - PressMax);
} 

if (BarLength > BarFull) {
  BarLength = BarFull;

}

     GLCD.FillRect(36,45,BarFull-1,3, WHITE);
     GLCD.FillRect(36,45,BarLength,3);
     GLCD.DrawLine(47, 43, 47, 46); // Green Pressure Min   
     GLCD.DrawLine(67, 43, 67, 46); // Green Pressure Max   
 
}
