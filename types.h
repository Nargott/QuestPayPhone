enum Mode {
  modeHello,
  modeSleep,
  modeNoCard,
  modeNumber,
  modeConnection,
  modeLineBusy,
  modeIncomingCall,
  modeOutcomingCall,
};

struct PlaySound {
  int number;
  enum {
    folderOutcomingCall = 0,
    folderCallSounds = 1,
    folderCallingSounds = 2,
    folderIncomingCall = 3,
    folderEmergencyCall = 4
  } folder;
};
