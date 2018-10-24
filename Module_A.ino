void Show_AData() {

if (Airspeed <10 ) {
  Airspeed = 0; 
 }

  textAreaSPEED.ClearArea();
  textAreaSPEED.Printf("%03d", Airspeed); 

  textAreaALT.ClearArea();
  textAreaALT.Printf("%05d", Altitude); //Altitude in ft

  textAreaVSIvalue.ClearArea();
  textAreaVSIvalue.Printf("%4d", abs(VertSpeed)); 

  textAreaVSIarrow.ClearArea();

  if (VertSpeed > 0) {
    textAreaVSIarrow.print("%"); // going UP
  }

  if (VertSpeed < 0) {
    textAreaVSIarrow.print("&"); // going DOWN
  }
  
}

void Show_OAT() {

// do something here
  
}

