void Show_VoltAmp() {
  float A_Max = 80;

  char buffer[5];

  GLCD.SelectFont(newbasic3x5);

  dtostrf(((float)EL_Volts/1000), 4, 1, buffer );  // it would be good to put proper Round function here.
  GLCD.CursorToXY(64, 1);
  GLCD.print(buffer);
  
  dtostrf(((float)EL_Amps*A_Max/1024), 4, 1, buffer );
  GLCD.CursorToXY(64, 11);
  GLCD.print(buffer);
}

