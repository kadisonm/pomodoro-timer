#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#include <TFT_ST7735.h>


// SCK = 13 and SDA == 11 (built in)

const int ROT_S1 = 3;
const int ROT_S2 = 4;
const int ROT_KEY = 5; 

const int BUZZER = 7;

int counter = 0;
int lastCounter = 0;
int s2State;
int lastS2State;


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
  // noTone(BUZZER);
}

int pomodoroLength = 15;
int breakLength = 15;

TextProperties title;
title.color = ST7735_BLACK;



void drawPomodoroMenu() {
  tft.fillScreen(ST7735_BLACK);

  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);

  drawText("Pomodoro", TextProperties{2});
  tft.setTextSize(1.7);
  tft.println("Click to start/stop timer");
  tft.println();
  tft.setTextSize(10);
  tft.println(pomodoroLength);

  
}

void drawBreakMenu() {
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.println("Pomodoro");
  tft.println();
  tft.setTextSize(10);
  tft.println("Click to start/stop timer");
}

void setup() {
  Serial.begin(9600);

  pinMode(ROT_KEY, INPUT_PULLUP);
  pinMode(ROT_S1, INPUT);
  pinMode(ROT_S2, INPUT);

  pinMode(BUZZER, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ROT_S1), updateRotEncoder, CHANGE);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(3);

  drawPomodoroMenu();
}

void loop() {
  updateRotEncoder();

  if (lastCounter != counter) {
    lastCounter = counter;
  }

  if (digitalRead(ROT_KEY) == LOW) {
    tft.fillScreen(ST7735_BLUE);
  }
}
