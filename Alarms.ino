void RedLightBlink(int OnOff) {
unsigned long duration = 500;
  
   if (OnOff == 1) {
      if (RedBlinkTimer == 0) {
        digitalWrite(42, HIGH);
        RedBlinkTimer = millis();
      } else {
        if (RedBlinkTimer + duration < millis()) {
          RedBlinkTimer = millis();
          digitalWrite(42, !digitalRead(42));
        }
      }
   } else {
      digitalWrite(42, LOW);
      RedBlinkTimer = 0;
   }
}

void YellowLightBlink(int OnOff) {
unsigned long duration = 500;
  
   if (OnOff == 1) {
      if (YellowBlinkTimer == 0) {
        digitalWrite(43, HIGH);
        YellowBlinkTimer = millis();
      } else {
        if (YellowBlinkTimer + duration < millis()) {
          YellowBlinkTimer = millis();
          digitalWrite(43, !digitalRead(43));
        }
      }
   } else {
      digitalWrite(43, LOW);
      YellowBlinkTimer = 0;
   }
}
