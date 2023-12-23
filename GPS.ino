void Init_GPS() {
// prepare the relevant static stuff on the screen  
    textAreaGPSDATA.print("GPS DATA");
    textAreaGSvalue.ClearArea();
    textAreaGPSaltvalue.ClearArea();
    textAreaGPSTRKvalue.ClearArea();
    textAreaGS.print("GS");
    textAreaGPSalt.print("ALT");
    textAreaGPSTRK.print("TRK");
    textAreaGSvalue.print(float(GroundSpeed)/100.0);   
    textAreaGPSaltvalue.print(GPSaltitude); 
    textAreaGPSTRKvalue.print(Tracking);
  }

void Show_GPS() {
  String s_GPSaltitude = "";
  String s_GroundSpeed = "";
  unsigned int tmp_GPSaltitude;
  
  tmp_GPSaltitude = GPSaltitude;
  
  if (GroundSpeed<100) {
    s_GroundSpeed = s_GroundSpeed + " ";
  }
    if (GroundSpeed<10) {
    s_GroundSpeed = s_GroundSpeed + " ";
  }

  s_GroundSpeed = s_GroundSpeed + GroundSpeed;
  textAreaGSvalue.ClearArea();
  textAreaGSvalue.print(s_GroundSpeed);   

  if (tmp_GPSaltitude < 10000) {
    s_GPSaltitude = s_GPSaltitude + " ";
  }

  if (tmp_GPSaltitude < 1000) {
    s_GPSaltitude = s_GPSaltitude + "  ";
  }

  if (tmp_GPSaltitude < 100) {
    s_GPSaltitude = s_GPSaltitude + " ";
  }

  if (tmp_GPSaltitude < 10) {
    s_GPSaltitude = s_GPSaltitude + " ";
  }

  if (tmp_GPSaltitude >= 1000) {
    s_GPSaltitude = s_GPSaltitude + int(tmp_GPSaltitude/1000) + ",";
    tmp_GPSaltitude = tmp_GPSaltitude - int(tmp_GPSaltitude/1000)*1000;
    
    if (tmp_GPSaltitude <100) {
        s_GPSaltitude = s_GPSaltitude + "0";
    }
  
    if (tmp_GPSaltitude <10) {
        s_GPSaltitude = s_GPSaltitude + "0";
    }
  } 
  
  s_GPSaltitude = s_GPSaltitude + tmp_GPSaltitude;

  textAreaGPSaltvalue.ClearArea();
  textAreaGPSaltvalue.print(s_GPSaltitude);
  

  textAreaGPSTRKvalue.ClearArea();
  textAreaGPSTRKvalue.print(Tracking);

}


// Show number of Satellites available and the current Singnal to Noise ratio for each constellation

void Show_GPS_SN_Graph(int msg_id) {
  unsigned int SN_Bar=0;
  int graph_offset=76;

  if (msg_id == 101) {
    graph_offset=76;
    textAreaGPSsats.ClearArea();
    textAreaGPSsats.print(Sat_SN[0]);
  } else {
    textAreaGLONASSsats.ClearArea();
    textAreaGLONASSsats.print(Sat_SN[0]);
    graph_offset=108;
  }


  for (int sat_ix = 1; sat_ix <= 7; sat_ix++) {
    SN_Bar=(Sat_SN[sat_ix] >> 4) & 0x0F;
    if (SN_Bar == 15) {
      SN_Bar = 0;
    }
    SN_Bar = SN_Bar/2;
    GLCD.DrawLine(graph_offset+sat_ix*2-1, 48, graph_offset+sat_ix*2-1, 42, 0); 
    GLCD.DrawLine(graph_offset+sat_ix*2-1, 48, graph_offset+sat_ix*2-1, 48-SN_Bar); 

    SN_Bar=(Sat_SN[sat_ix]) & 0x0F;
    if (SN_Bar == 15) {
      SN_Bar = 0;
    }
    SN_Bar = SN_Bar/2;
    GLCD.DrawLine(graph_offset+sat_ix*2, 48, graph_offset+sat_ix*2, 42, 0); 
    GLCD.DrawLine(graph_offset+sat_ix*2, 48, graph_offset+sat_ix*2, 48-SN_Bar); 


  }
}

