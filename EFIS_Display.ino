void EFIS_Display() {  
  //Draw display layout
  GLCD.ClearScreen();


  GLCD.DrawRoundRect(0,0,64,23,3); //around ASI
  GLCD.DrawRoundRect(0,22,64,21,3); //around Time
  GLCD.DrawRoundRect(0,42,64,22,3); //around HDG
  
                 
  GLCD.DrawRoundRect(129,0,63,29,3); //around the Altitude
  GLCD.DrawRoundRect(129, 28, 63, 13, 3); //around the QNH
  GLCD.DrawRoundRect(129,40,63,24,3); //around the VSI


  GLCD.DrawRect(65, 0, 63, 52); //around the Horizon
  GLCD.DrawRoundRect(65, 53, 63, 11, 3); 
 
  
  //************TEXT AREAS*******************

  //***************** IAS *******************
  textAreaSPEED.DefineArea(4, 3 , 3, 1 , lcdnums12x16);
  textAreaIAS.DefineArea(49, 1 , 3, 1 , newbasic3x5);
  textAreaIAS.print("ASI");
  textAreaKTS.DefineArea(43, 12 , 3, 1 , System5x7);
  textAreaKTS.print("Kts");

  //***************** Heading *******************
  textAreaMAG.DefineArea(18, 45 , 3, 1 , lcdnums12x16);
  textAreaHDG.DefineArea(4, 54 , 3, 1 , newbasic3x5);
  textAreaHDG.print("HDG");
  textAreaDEG.DefineArea(55, 44 , 1, 1 , System5x7);
  textAreaDEG.print("o");
  textAreaMagCal.DefineArea(4, 44 , 1, 1 , newbasic3x5);

 //***************** Time *******************

  textAreaTimeMaster.DefineArea(3, 24 , 1, 1 , newbasic3x5);
  if (TimeMaster == 1) {
    textAreaTimeMaster.print("*");
  }
  textAreaUTC.print("LOC");
  textAreaUTC.DefineArea(8, 24 , 3, 1 , newbasic3x5);
  if (TimeConfig == 1) {
    textAreaUTC.print("LOC");
  } else {
    textAreaUTC.print("UTC");
  }
  textAreaUTCTime.DefineArea(25, 24 , 8, 1 , newbasic3x5);
  textAreaFLT.DefineArea(8, 32 , 3, 1 , newbasic3x5);
  textAreaFLT.print("FLT");
  textAreaFLTTime.DefineArea(25, 32 , 8, 1 , newbasic3x5);

  //*************** Altidute ****************************
  textAreaALT.DefineArea(130, 2 , 5, 1 , lcdnums12x16);
  textAreaALTFT.DefineArea(134, 19 , 14, 1 , newbasic3x5);
  textAreaALTFT.print("ALT         FT");

  //********************** QNH **************************
  textAreaQNH.DefineArea(136, 31, 3, 1 , System5x7);
  textAreaQNH.print("QNH");
  textAreaQNHvalue.DefineArea(160, 31 , 4, 1 , System5x7);


  //*********************** VSI *************************
  textAreaVSIvalue.DefineArea(146, 47 , 4, 1 , Verdana12_bold);
  textAreaVSI.DefineArea(132, 51 , 3, 1 , newbasic3x5);
  textAreaVSI.print("VSI");
  
  textAreaVSIarrow.DefineArea(177, 47 , 1, 1 , Arrows);

  //**************** Misc extra fields at the bottom
  textAreaBottomL.DefineArea(68, 43 , 4, 1 , newbasic3x5);
  textAreaBottomL.print("0");
  textAreaBottomR.DefineArea(110, 43 , 4, 1 , newbasic3x5);
  textAreaBottomR.print("0");
  textAreaGmeter.DefineArea(84, 43 , 6, 1 , newbasic3x5);

  //**************** GPS area *******************
  textAreaGPSDATA.DefineArea(81, 1 , 8, 1 , newbasic3x5);
  textAreaGS.DefineArea(69, 12, 3, 1 , System5x7);
  textAreaGSvalue.DefineArea(94, 12, 3, 1 , System5x7);
  textAreaGPSalt.DefineArea(69, 22, 4, 1 , System5x7);
  textAreaGPSaltvalue.DefineArea(94, 22, 5, 1 , System5x7);
  textAreaGPSTRK.DefineArea(69, 32, 4, 1 , System5x7);
  textAreaGPSTRKvalue.DefineArea(94, 32, 5, 1 , System5x7);

//  textAreaGS.print("GS:");


  textAreaQNHvalue.ClearArea();
  textAreaQNHvalue.Printf("%04d", QNH);

}
