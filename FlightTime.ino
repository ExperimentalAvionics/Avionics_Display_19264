void FlightTime() {
  String s_UTC = "";
  byte second, minute, hour, dayOfWeek, dayOfMonth, month;
  int year;
  // retrieve data from RTC

  DateTime now = RTC.now();
  hour = now.hour();
  minute = now.minute();
  second = now.second();

  textAreaUTCTime.ClearArea();

  if (hour < 10) {
    s_UTC += "0";
    
  }
    s_UTC += hour;
    s_UTC += ":";
    
  if (minute < 10) {
    s_UTC += "0";
    
  }
    s_UTC += minute;
    s_UTC += ":";  
    
  if (second < 10) {
    s_UTC += "0";
    
  }
    s_UTC += second;
  
  textAreaUTCTime.print(s_UTC);
  
  
  if (Airspeed > MinFlightSpeed and FlightStartMarker == 0) { //we reached flying speed and it is time to start the timer
    FlightStartMarker = millis();
  }

  if (Airspeed > MinFlightSpeed and FlightStartMarker > 0) { //we are flying so keep track of the time
    FlyingTime = millis() - FlightStartMarker;
  }
  
  textAreaFLTTime.ClearArea();
  textAreaFLTTime.print(Time_Millis2String(FlyingTime));
  
}


String Time_Millis2String(unsigned long LongTime) {
  String s_Time = "";
  int h,m,s;
  s = LongTime / 1000;
  m = s / 60;
  h = s / 3600;
  s = s - m * 60;
  m = m - h * 60;

  if (h < 10) {
    s_Time += "0";
  }
    s_Time += h;
    s_Time += ":";

  if (m < 10) {
    s_Time += "0";
  }
    s_Time += m;
    s_Time += ":";
  
  if (s < 10) {
    s_Time += "0";
  }
    s_Time += s;

  return s_Time;
}

byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}

byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
