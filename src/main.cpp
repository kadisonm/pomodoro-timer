#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// TFT ORDER
// LED (CONNECT TO 3.3V)
// SCK
// SDA
// AO
// RESET
// CS
// GND
// VCC

const int TFT_CS = 8; // Clock Signal
const int TFT_RESET = 9;
const int TFT_AO = 10; // Data command
// SCK = 13 and SDA == 11 (built in)

const int ROT_S1 = 3;
const int ROT_S2 = 4;
const int ROT_KEY = 5; 

const int BUZZER = 7;

int counter = 0;
int lastCounter = 0;
int s2State;
int lastS2State;


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_AO, TFT_RESET);

void updateScreen() {
  tft.fillScreen(ST7735_WHITE);
  tft.setCursor(0, 0);
  tft.println("Welcome");
  tft.println("-------");
  tft.println("Encoder Position: " + String(counter));
}

void updateRotEncoder() {
  s2State = digitalRead(ROT_S2);

  // Pulse occured
  if (s2State == HIGH && lastS2State == LOW){     
    // Anti-clockwise
    if (digitalRead(ROT_S1) == HIGH) { 
      counter++;
    } else {
      counter--;
    }
  } 

  lastS2State = s2State;
}

void playNote(int freq, int dur) {
  tone(BUZZER, freq, dur);
  delay(dur * 1.30);
}


void playTune() {
    playNote(660, 100);  // E5
    delay(100);
    playNote(660, 100);  // E5
    delay(100);
    playNote(660, 100);  // E5
    delay(100);
    playNote(510, 100);  // C5
    playNote(660, 100);  // E5
    delay(100);
    playNote(770, 100);  // G5
    delay(300);
    playNote(380, 100);  // G4
    delay(300);
  
    playNote(510, 100);  // C5
    delay(100);
    playNote(380, 100);  // G4
    delay(100);
    playNote(320, 100);  // E4
    delay(200);
    playNote(440, 100);  // A4
    delay(100);
    playNote(480, 100);  // A#4
    delay(100);
    playNote(450, 100);  // A4
    delay(100);
    playNote(430, 100);  // G#4
    delay(100);
    playNote(380, 100);  // G4
    delay(100);
    playNote(660, 100);  // E5
    delay(100);
    playNote(760, 100);  // G5
    playNote(860, 100);  // A5
    delay(100);
    playNote(700, 100);  // F5
    playNote(760, 100);  // G5
    delay(100);
    playNote(660, 100);  // E5
    delay(100);
    playNote(520, 100);  // C5
    delay(100);
    playNote(580, 100);  // D5
    playNote(480, 100);  // A#4
  
    noTone(BUZZER);
}

void setup() {
  Serial.begin(9600);

  pinMode(ROT_KEY, INPUT_PULLUP);
  pinMode(ROT_S1, INPUT);
  pinMode(ROT_S2, INPUT);

  pinMode(BUZZER, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ROT_S1), updateRotEncoder, CHANGE);

  tft.initR(INITR_BLACKTAB);

  tft.setTextColor(ST7735_BLACK);
  tft.setTextSize(1.7);

  updateScreen();

  playTune();
}

void loop() {
  updateRotEncoder();

  if (lastCounter != counter) {
    updateScreen();
    lastCounter = counter;
  }

  if (digitalRead(ROT_KEY) == LOW) {
    tft.fillScreen(ST7735_BLUE);
    delay(500);
    updateScreen();
  }
}
