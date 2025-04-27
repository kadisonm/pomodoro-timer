#include <Arduino.h>

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

TextProperties title;
TextProperties subtitle;

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

void drawPomodoroMenu() {
  tft.fillScreen(ST7735_BLACK);

  drawText("Pomodoro", title);

  title.y = 40;
  title.horizontalAnchor = "left";
  drawText("Pomodoro", title);

  title.y = 80;
  title.horizontalAnchor = "right";
  drawText("Pomodoro", title);
  //drawText("Click to start/stop timer", subtitle);
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

  // Set up text types
  title.x = tftWidth / 2;
  title.y = 0;
  title.size = 2.2;
  title.horizontalAnchor = "center";
  title.verticalAnchor = "bottom";

  subtitle.x = tftHeight / 2;
  subtitle.y = 2;
  subtitle.size = 1.7;
  subtitle.horizontalAnchor = "center";

  pinMode(ROT_KEY, INPUT_PULLUP);
  pinMode(ROT_S1, INPUT);
  pinMode(ROT_S2, INPUT);

  pinMode(BUZZER, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ROT_S1), updateRotEncoder, CHANGE);

  initTFT();

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
