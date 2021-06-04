void Init_Screen() {
  switch (DisplayScreen) {
      case 1:   // EFIS
          //********************* Read EEPROM  ***************************
          QNH             = EEPROM.get(QNH_MemOffset, QNH);
          MinFlightSpeed  = EEPROM.get(MinFlightSpeed_MemOffset, MinFlightSpeed);
          TimeConfig   = EEPROM.get(TimeConfig_MemOffset, TimeConfig);
          //******************** End reading EEPROM

          EFIS_Display();
          
          ForceDisplay = 1;
          Show_AData();
          
          ForceDisplay = 1;
          Show_Heading();
          
          ForceDisplay = 1;
          Show_Accel();
          
          if(MidScreen == 1) {
            Init_GPS();
            ForceDisplay = 1;
            Show_GPS(); 
          }
          if(MidScreen == 2) {
            Init_TAS();  
            ForceDisplay = 1;
            Show_TAS(); 
          }
          break;
      case 2:   // EMS
          EMS_Display();
          break;
  }
  
}
