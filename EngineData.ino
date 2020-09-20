void RightScreenDefault() {
//************ EGT + CHT ****************************
  
   GLCD.DrawLine(82, 0, 82, 63);

   if (CYL == 4) {
     GLCD.DrawLine(82, 24, 195, 24);
     GLCD.CursorToXY(85, 0);
     GLCD.print("E");
     GLCD.CursorToXY(85, 8);
     GLCD.print("G");
     GLCD.CursorToXY(85, 16);
     GLCD.print("T");
  
     GLCD.CursorToXY(85, 25);
     GLCD.print("C");
     GLCD.CursorToXY(85, 33);
     GLCD.print("H");
     GLCD.CursorToXY(85, 41);
     GLCD.print("T");
     GLCD.DrawLine(82, 49, 195, 49);
   } else {
     GLCD.DrawLine(82, 32, 195, 32);
     GLCD.CursorToXY(85, 3);
     GLCD.print("E");
     GLCD.CursorToXY(85, 11);
     GLCD.print("G");
     GLCD.CursorToXY(85, 19);
     GLCD.print("T");
  
     GLCD.CursorToXY(85, 35);
     GLCD.print("C");
     GLCD.CursorToXY(85, 44);
     GLCD.print("H");
     GLCD.CursorToXY(85, 53);
     GLCD.print("T");
   }
   InitEGT(1);
   InitEGT(2);
   InitEGT(3);
   InitEGT(4);
   if (CYL == 6) {
     InitEGT(5);
     InitEGT(6);
   }

   InitCHT(1);
   InitCHT(2);
   InitCHT(3);
   InitCHT(4);
   if (CYL == 6) {
     InitCHT(5);
     InitCHT(6);
   }

}
//****************** End of EGT + CHT **************


// Data for the alternative right side of the screen

void EngineAltData1() {
  char buffer[5];
// refresh data on the screen every 500ms
  if (millis() - RightScreenTimer > 500) {

    dtostrf(((float)OilTemperature/10), 5, 0, buffer );
    textAreaEMSAltValue1.ClearArea();
    textAreaEMSAltValue1.print(buffer);

    dtostrf(((float)OilPressure/1000), 5, 1, buffer );
    textAreaEMSAltValue2.ClearArea();
    textAreaEMSAltValue2.print(buffer);

    dtostrf(((float)FuelPressure/1000), 5, 1, buffer );
    textAreaEMSAltValue3.ClearArea();
    textAreaEMSAltValue3.print(buffer);

    dtostrf(((float)EL_AltAmps/1000), 5, 1, buffer );
    textAreaEMSAltValue4.ClearArea();
    textAreaEMSAltValue4.print(buffer);

    dtostrf(((float)EL_BatAmps/1000), 5, 1, buffer );
    textAreaEMSAltValue5.ClearArea();
    textAreaEMSAltValue5.print(buffer);

    dtostrf(((float)EL_Volts/1000), 5, 1, buffer );
    textAreaEMSAltValue6.ClearArea();
    textAreaEMSAltValue6.print(buffer);
    
    RightScreenTimer = millis();
  }
}
