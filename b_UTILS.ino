void changeMode(Mode m) {
  enteredNumber = "";
  currentMode = m;
  lcd.noBlink();
  lcd.noCursor();
  lcd.clear();
  delay(10);
  mp3.stop();
  IsModeChanged = true;
}

void PrintOnce(String msg, int row) {
  if (IsModeChanged) {
    lcd.setCursor(0, row);
    lcd.print(msg);
    IsModeChanged = false;
  }
}

void readKeypadNumber(int len) {
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case 'D': {
          enteredNumber = "";
          lcd.clear();
        } break;
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9': {
          enteredNumber += String(key);
          if (enteredNumber.length() == len) {
            call(enteredNumber);
            return;
          }
        } break;
    }
    lcd.blink();
    lcd.setCursor(0, 1);
    lcd.print(enteredNumber);
    lcd.setCursor(enteredNumber.length(), 1);

  }
}

void readKeypadFunction() {
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case 'C': {
          mp3.increaseVolume();
          uint16_t volume = mp3.getVolume();
          Serial.print("volume ");
          Serial.println(volume);
        } break;
    }
  }

}

void playSound(PlaySound ps) {
  if (ps.folder == PlaySound::folderOutcomingCall) {
    mp3.playMp3FolderTrack(ps.number);
    return;
  }

  mp3.playFolderTrack16(ps.folder, ps.number);
}

void call(String number) {
  int arrSize;
  bool isNumberValid = false;

  if (number.length() == NumbersEmergency[0].length()) { //if emergency call
    arrSize = (sizeof(NumbersEmergency) / sizeof(String));
    for (int i = 0; i < arrSize; i++) {
      if (number == NumbersEmergency[i]) {
        callingAnswer = {.number = i+1, .folder = PlaySound::folderEmergencyCall};
        isNumberValid = true;
        break;
      }
    }
  }

  arrSize = (sizeof(Numbers) / sizeof(String));
  for (int i = 0; i < arrSize; i++) {
    if (number == Numbers[i]) {
      callingAnswer = {.number = i+1, .folder = PlaySound::folderOutcomingCall};
      isNumberValid = true;
    }
  }
  
  
  if (!isNumberValid) {
    changeMode(modeLineBusy);
    playSound(SoundLineBusy);
    return;
  }

  changeMode(modeConnection);
  lcd.noBlink();
  lcd.setCursor(0, 0);
  lcd.print(F("CALLING: "));
  lcd.setCursor(0, 1);
  lcd.print(number);
  playSound(SoundConnection);
}

void processPlayEnded() {
    switch(currentMode){
      case modeConnection: {
        lcd.setCursor(0, 0);
        lcd.print(F("CALLING"));
        changeMode(modeOutcomingCall);
        playSound(callingAnswer);
      } break;
      case modeLineBusy: {
        changeMode(modeNoCard);
      } break;
      case modeOutcomingCall: case modeIncomingCall: {
        changeMode(modeLineBusy);
      } break;
    }
}
