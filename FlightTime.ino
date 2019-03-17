void FlightTime() {
  String s_UTC = "";
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
//  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
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

/*
void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}
*/
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}

byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
/*
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
*/
