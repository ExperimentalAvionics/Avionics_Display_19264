void Init_Screen() {
  switch (DisplayScreen) {
      case 1:   // EFIS
          //********************* Read EEPROM  ***************************
          QNH             = EEPROM.get(QNH_MemOffset, QNH);
          MinFlightSpeed  = EEPROM.get(MinFlightSpeed_MemOffset, MinFlightSpeed);
          //******************** End reading EEPROM
          //setDS3231time(00,20,8,7,18,06,16);
          EFIS_Display();
          break;
      case 2:   // EMS
          EMS_Display();
          break;
  }
  
}

