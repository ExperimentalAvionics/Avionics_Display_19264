void EMS_Display() {  
  //Draw display layout
  GLCD.ClearScreen();

  textAreaRPM.DefineArea(22, 2, 3, 1 , Verdana12_bold);

  GLCD.DrawRect(0,8,10,49);
  GLCD.SelectFont(newbasic3x5);
  GLCD.CursorToXY(0, 57);
  GLCD.print("FUEL");

// fuel markers
  GLCD.DrawLine(8, 32, 11, 32); // 3/4
  GLCD.DrawLine(8, 20, 11, 20); // 1/2
  GLCD.DrawLine(8, 44, 11, 44); // 1/4

// *************** end of fuel box

  GLCD.DrawLine(14, 0, 14, 41);
  GLCD.DrawLine(55, 0, 55, 23);
  GLCD.DrawLine(14, 41, 14, 55);
  GLCD.DrawLine(14, 55, 82, 55);

  GLCD.SelectFont(newbasic3x5);
  GLCD.CursorToXY(17, 14);
  GLCD.print("RPM");
  GLCD.DrawLine(14, 23, 82, 23);

  // **** endurance box *****************
  // GLCD.CursorToXY(17, 25);
  //GLCD.print("FL");
  GLCD.DrawLine(14, 41, 82, 41);

// *********** OIL ***************
   GLCD.CursorToXY(16, 44);
   GLCD.print("O");
   GLCD.CursorToXY(22, 44);
   GLCD.print("P/T");
   GLCD.DrawRect(35,43,46,11);

   
//************* Fuel pressure ****************
   GLCD.CursorToXY(18, 57);
   GLCD.print("PR.");
   GLCD.DrawRect(35,57,46,7);


// ********** VoltAmp *************

  GLCD.SelectFont(newbasic3x5);
  GLCD.CursorToXY(58, 1);
  GLCD.print("V");
  GLCD.CursorToXY(58, 11);
  GLCD.print("A");

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

//****************** End of EGT + CHT **************

}
