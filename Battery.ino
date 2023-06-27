//Backup battery stuff

void Show_BAT() {

char buffer[5];

  GLCD.SelectFont(newbasic3x5);

  dtostrf(((float)BAT_Volts/1000), 4, 1, buffer );  // it would be good to put proper Round function here.
  textBatVoltValue.ClearArea();
  textBatVoltValue.Printf(buffer); 

  textBatTempValue.ClearArea();
  textBatTempValue.print(BAT_Temperature); 

  switch (BAT_Status) {
    case 0:
      textBatStatus.print("-POWER LOST-"); 
    break;
    case 1:
      textBatStatus.print("S:2 GONE MAD");
    break;
    case 2:
      // input power is OK but charge is stopped
      if (BAT_Volts > 12000 and BAT_Temperature> 0 and BAT_Temperature < 50) {
        textBatStatus.print("BATTERY FULL"); 
      } else if (BAT_Temperature <= 0) {
        textBatStatus.print("BAT TOO COLD"); 
      } else if (BAT_Temperature >= 50) {
        textBatStatus.print(" BAT TOO HOT"); 
      } else {
        textBatStatus.print("TIMEOUT >3HR"); 
      }
    break;
    case 3:
      textBatStatus.print("  CHARGING  ");
    break;
    default:
      textBatStatus.print("UNDEF STATUS");
    break;
    }  
}
