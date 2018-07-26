void wakeUp() {
    // Just a handler for the pin interrupt.
    //Serial.println("interrupt!");
}

class PlayerNotifications {
public:
  static void OnError(uint16_t errorCode)
  {
    // see DfMp3_Error for code meaning
    Serial.print("Com Error ");
    Serial.println(errorCode);
  }

  static void OnPlayFinished(uint16_t globalTrack)
  {
    Serial.print("Play finished for #");
    Serial.println(globalTrack);
    processPlayEnded();
  }

  static void OnCardOnline(uint16_t code)
  {
    Serial.print("Card online ");
    Serial.println(code);     
  }

  static void OnCardInserted(uint16_t code)
  {
    Serial.print("Card inserted ");
    Serial.println(code); 
  }

  static void OnCardRemoved(uint16_t code)
  {
    Serial.print("Card removed ");
    Serial.println(code);  
  }
};
