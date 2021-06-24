void Init_GPS() {
// prepare the relevant static stuff on the screen  
    textAreaGPSDATA.print("GPS DATA");
    textAreaGSvalue.ClearArea();
    textAreaGPSaltvalue.ClearArea();
    textAreaGPSTRKvalue.ClearArea();
    textAreaGS.print("GS:");
    textAreaGPSalt.print("ALT:");
    textAreaGPSTRK.print("TRK:");
    textAreaGSvalue.print(float(GroundSpeed)/100.0);   
    textAreaGPSaltvalue.print(GPSaltitude); 
    textAreaGPSTRKvalue.print(Tracking);
  }

void Show_GPS() {

  textAreaGSvalue.ClearArea();
  textAreaGSvalue.print(GroundSpeed);   

  textAreaGPSaltvalue.ClearArea();
  textAreaGPSaltvalue.print(GPSaltitude);

  textAreaGPSTRKvalue.ClearArea();
  textAreaGPSTRKvalue.print(Tracking);

  
}
