void Show_RPM() {

  //GLCD.SelectFont(Verdana12_bold);
 // GLCD.CursorToXY(20, 2);
  textAreaRPM.ClearArea();
  textAreaRPM.Printf("%04d", RPM); 

  //GLCD.print(RPM);

 
}

void Show_TT() {

 char outstr[7];
// show engine time
  GLCD.SelectFont(newbasic3x5);
  GLCD.CursorToXY(31, 14);
  dtostrf(((float)TT_Clock/3600), 6, 1, outstr );
  GLCD.print(outstr);
  
}

