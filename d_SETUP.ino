void setup() {
  lcd.begin();
  lcd.backlight();

  //inputs
  pinMode(PIN_HANDSET, INPUT);
  pinMode(PIN_CASE, INPUT);
  pinMode(PIN_CARD, INPUT);
  //pinMode(PIN_RADIO_A, INPUT);
  pinMode(PIN_RADIO_B, INPUT);
  //pinMode(PIN_RADIO_C, INPUT);
  pinMode(PIN_RADIO_D, INPUT);

  //outputs
  pinMode(PIN_SPEAKER_RELAY, OUTPUT);

  Serial.begin(9600);

  delay(500);
  mp3.begin();
  delay(500);

  mp3.setVolume(15); //30 -- MAX
  uint16_t volume = mp3.getVolume();
  Serial.print("volume ");
  Serial.println(volume);
    
  Serial.println("starting...");
  //mp3.playGlobalTrack(1);
  //mp3.playFolderTrack16(3, 1);
  //mp3.playMp3FolderTrack(1);
  //delay(50000);
  mp3.setRepeatPlay(false);
//  Serial.println("getTotalTrackCount: ");
//  Serial.println(mp3.getTotalTrackCount());
//  Serial.println("track ");
//  Serial.println(mp3.getCurrentTrack());
}
