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

  // **** Flow and Endurance box *****************
  // GLCD.CursorToXY(17, 25);
  //GLCD.print("FL");
  textFlowLabel.DefineArea(18, 24 , 14, 1 , newbasic3x5);
  textEndurLabel.DefineArea(18, 32 , 14, 1 , newbasic3x5);
  textFlowLabel.print("FL      /     ");
  textEndurLabel.print("EN      /     ");
  textFlowActual.DefineArea(30, 24 , 4, 1 , newbasic3x5);
  textFlowPlanned.DefineArea(62, 24 , 4, 1 , newbasic3x5);
  textEndurActual.DefineArea(30, 32 , 4, 1 , newbasic3x5);
  textEndurPlanned.DefineArea(62, 32 , 4, 1 , newbasic3x5);
  
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
  
  RightScreenDefault();
  
//****************** End of EGT + CHT **************

  //**************** Alternative Engine Data area *******************
  textAreaEMSAltKey1.DefineArea(90, 0 , 8, 1 , System5x7);
  textAreaEMSAltValue1.DefineArea(140, 0 , 5, 1 , System5x7);
  textAreaEMSAltLabel1.DefineArea(174, 0 , 3, 1 , System5x7);

  textAreaEMSAltKey2.DefineArea(90, 11 , 8, 1 , System5x7);
  textAreaEMSAltValue2.DefineArea(140, 11 , 5, 1 , System5x7);
  textAreaEMSAltLabel2.DefineArea(174, 11 , 3, 1 , System5x7);

  textAreaEMSAltKey3.DefineArea(90, 22 , 8, 1 , System5x7);
  textAreaEMSAltValue3.DefineArea(140, 22 , 5, 1 , System5x7);
  textAreaEMSAltLabel3.DefineArea(174, 22 , 3, 1 , System5x7);

  textAreaEMSAltKey4.DefineArea(90, 34 , 8, 1 , System5x7);
  textAreaEMSAltValue4.DefineArea(140, 34 , 5, 1 , System5x7);
  textAreaEMSAltLabel4.DefineArea(174, 34 , 3, 1 , System5x7);

  textAreaEMSAltKey5.DefineArea(90, 45 , 8, 1 , System5x7);
  textAreaEMSAltValue5.DefineArea(140, 45 , 5, 1 , System5x7);
  textAreaEMSAltLabel5.DefineArea(174, 45 , 3, 1 , System5x7);

  textAreaEMSAltKey6.DefineArea(90, 56 , 8, 1 , System5x7);
  textAreaEMSAltValue6.DefineArea(140, 56 , 5, 1 , System5x7);
  textAreaEMSAltLabel6.DefineArea(174, 56 , 3, 1 , System5x7);

}
