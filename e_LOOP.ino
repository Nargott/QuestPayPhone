void loop() {
  mp3.loop();
  switch (currentMode) {
    case modeHello: {
        PrintOnce(F("HELLO! SYS INIT..."), 0);
        delay(2000);
        changeMode(modeSleep);
      } break;
    case modeSleep: {
        lcd.noDisplay(); 
        lcd.noBacklight();
        // Allow wake up pin to trigger interrupt on low.
        attachInterrupt(0, wakeUp, RISING);
        attachInterrupt(1, wakeUp, RISING);

        LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

        // Disable external pin interrupt on wake up pin.
        detachInterrupt(0);
        detachInterrupt(1);
        lcd.display();
        lcd.backlight();
        changeMode(modeNoCard);
      } break;
    case modeNoCard: {
        if ((Handset.update()) && (digitalRead(PIN_HANDSET) == LOW)) changeMode(modeSleep);
        if (IsModeChanged) { //reset sound
          mp3.setVolume(15); //31 -- MAX
        }
        if (digitalRead(PIN_CARD) == LOW) {
          PrintOnce(F("INSERT CARD!"), 0);
          readKeypadNumber(NumberLenEmergency);
        } else {
          changeMode(modeNumber);
        }
      } break;
    case modeNumber: {
        if ((Handset.update()) && (digitalRead(PIN_HANDSET) == LOW)) changeMode(modeSleep);
        if ((Card.update()) && (digitalRead(PIN_CARD) == LOW)) changeMode(modeNoCard);
        PrintOnce(F("ENTER NUMBER:"), 0);
        readKeypadNumber(NumberLen);
      } break;
    case modeLineBusy: {
        if ((Handset.update()) && (digitalRead(PIN_HANDSET) == LOW)) changeMode(modeSleep);
        PrintOnce(F("CALL ENDED"), 0);
      } break;
    case modeOutcomingCall: {
      if ((Handset.update()) && (digitalRead(PIN_HANDSET) == LOW)) changeMode(modeSleep);
      readKeypadFunction();
    } break;
    case modeIncomingCall: case modeConnection: {
        if ((Handset.update()) && (digitalRead(PIN_HANDSET) == LOW)) changeMode(modeSleep);
        readKeypadFunction();
        //if ((Card.update()) && (digitalRead(PIN_CARD) == LOW)) changeMode(modeNoCard);
        
      } break;
  }
//    if ((digitalRead(PIN_RADIO_A) == HIGH)) {
//      Serial.println("PIN_RADIO_A");
//    }
    if ((radioChannelB.update()) && (digitalRead(PIN_RADIO_B) == HIGH)) {
      Serial.println(F("PIN_RADIO_B"));
    }
//    if ((digitalRead(PIN_RADIO_C) == HIGH)) {
//      Serial.println("PIN_RADIO_C");
//    }
    if ((radioChannelD.update()) && (digitalRead(PIN_RADIO_D) == HIGH)) {
      Serial.println(F("PIN_RADIO_D"));
    }
}


