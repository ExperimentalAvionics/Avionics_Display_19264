void RedLightBlink(int OnOff) {
unsigned long duration = 500;
  
   if (OnOff == 1) {
      if (RedBlinkTimer == 0) {
        digitalWrite(42, HIGH);
        analogWrite(9, LEDBrightness);
        RedBlinkTimer = millis();
      } else {
        if (RedBlinkTimer + duration < millis()) {
          RedBlinkTimer = millis();
          digitalWrite(42, !digitalRead(42));
          if (digitalRead(42) == LOW) { // use digital pin ststus to track the status of LED. Doggy hack
            analogWrite(9, 0);
          } else {
            analogWrite(9, LEDBrightness);
          }
        }
      }
   } else {
      digitalWrite(42, LOW);
      analogWrite(9, 0);
      RedBlinkTimer = 0;
   }
}

void YellowLightBlink(int OnOff) {
unsigned long duration = 500;
  
   if (OnOff == 1) {
      if (YellowBlinkTimer == 0) {
        digitalWrite(43, HIGH);
        analogWrite(8, LEDBrightness);
        YellowBlinkTimer = millis();
      } else {
        if (YellowBlinkTimer + duration < millis()) {
          YellowBlinkTimer = millis();
          digitalWrite(43, !digitalRead(43));
          if (digitalRead(43) == LOW) { // use digital pin ststus to track the status of LED. Doggy hack
            analogWrite(8, 0);
          } else {
            analogWrite(8, LEDBrightness);
          }
        }
      }
   } else {
      digitalWrite(43, LOW);
      analogWrite(8, 0);
      YellowBlinkTimer = 0;
   }
}
