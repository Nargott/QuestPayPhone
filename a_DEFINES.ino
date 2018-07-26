//#include <MemoryFree.h>
#include <Bounce.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <LowPower.h>
#include <SoftwareSerial.h>
#include <DFMiniMp3.h>
#include "types.h"

//pins defines
#define PIN_SOFT_RX 8
#define PIN_SOFT_TX 9
#define PIN_SPEAKER_RELAY 0 //RXO pin, has a button "prog", must be swithed before programming or serial debug
#define PIN_REMOTE_INT 2
#define PIN_HANDSET 3 //phone handset raised pin
#define PIN_CASE A1
#define PIN_CARD A2
#define I2C_ADDR_SCREEN 0x27
#define I2C_ADDR_RTC 
#define PIN_RADIO_A A7 //???
#define PIN_RADIO_B A0 // ok
#define PIN_RADIO_C A6 //???
#define PIN_RADIO_D A3 // ok

//sounds defines
#define SOUND_CALL 1
#define SOUND_CONNECTION 1
#define SOUND_LINE_BUSY 2

//screen init section
LiquidCrystal_I2C lcd(0x27, 16, 2);

//keypad init section
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {4, 5, 6, 7}; //row pinouts of the keypad
byte colPins[COLS] = {12, 13, 10, 11}; //column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//func declarations
class PlayerNotifications;
void changeMode(Mode m);
void playSound(PlaySound ps);

//player init section
SoftwareSerial secondarySerial(PIN_SOFT_RX, PIN_SOFT_TX); // RX, TX
DFMiniMp3<SoftwareSerial, PlayerNotifications> mp3(secondarySerial);

//remote radio init section
//Bounce radioChannelA = Bounce(PIN_RADIO_A, 1);
Bounce radioChannelB = Bounce(PIN_RADIO_B, 1);
//Bounce radioChannelC = Bounce(PIN_RADIO_C, 1);
Bounce radioChannelD = Bounce(PIN_RADIO_D, 1);
Bounce Handset = Bounce(PIN_HANDSET, 4);
Bounce Card = Bounce(PIN_CARD, 4);

//global vars section
const int NumberLenEmergency = 2;
const int NumberLen = 7;

const PlaySound SoundConnection = {.number = SOUND_CONNECTION, .folder = PlaySound::folderCallingSounds};
const PlaySound SoundLineBusy = {.number = SOUND_LINE_BUSY, .folder = PlaySound::folderCallingSounds};

String enteredNumber = "";
Mode currentMode = modeHello;
bool IsModeChanged = true;
PlaySound callingAnswer;
