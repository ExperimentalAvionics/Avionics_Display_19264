void Send_QNH() {
  buf[0] = QNH;
  buf[1] = QNH >> 8;
  CAN.sendMsgBuf(46, 0, 2, buf); 
}


void setQNH() {
  int encCurrentValue = 0;

  encCurrentValue = myEnc.read()/4;
  
  if (encCurrentValue != encLastValue) {

   QNH = QNH + (encCurrentValue - encLastValue);
   encLastValue = encCurrentValue;
   //textAreaQNHvalue.ClearArea();
   textAreaQNHvalue.Printf("%04d", QNH);
   GLCD.InvertRect(160, 31, 24, 8);
   Send_QNH();
  }

   buttonState = digitalRead(Click_Button);

  if (buttonState == LOW and bTimer == 0) {
    bTimer = millis();
  }

  if (buttonState == HIGH and bTimer > 0) {  //finished plying with QNH, save it and exit
    EEPROM.put(QNH_MemOffset, QNH);
    bTimer = 0;
    MenuItem = 0;
    GLCD.InvertRect(132, 30,57,9);
  }


//  Send_QNH();
    
  }
