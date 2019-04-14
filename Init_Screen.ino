void Init_Screen() {
  switch (DisplayScreen) {
      case 1:   // EFIS
          //********************* Read EEPROM  ***************************
          QNH             = EEPROM.get(QNH_MemOffset, QNH);
          MinFlightSpeed  = EEPROM.get(MinFlightSpeed_MemOffset, MinFlightSpeed);
          TimeConfig   = EEPROM.get(TimeConfig_MemOffset, TimeConfig);
          //******************** End reading EEPROM

          EFIS_Display();
          break;
      case 2:   // EMS
          EMS_Display();
          break;
  }
  
}
