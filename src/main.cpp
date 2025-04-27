#include <Arduino.h>

#include <TFT_ST7735.h>
#include <Rotary_Encoder.h>
#include <Buzzer.h>

TextProperties title;
TextProperties subtitle;
TextProperties time;

String menu = "pomodoro";

boolean timerStarted = false;

int pomodoroLength = 15;
int breakLength = 5;

void showPomodoroMenu() {
  setBackground(ST7735_BLACK);
  drawText("Pomodoro", title);
  drawText("Click to start/stop timer", subtitle);
}

void showPomodoroTimer() {
  drawText("Pomodoro", title);
  drawText("Click to start/stop timer", subtitle);
  drawText(String(pomodoroLength).c_str(), time);
}

void showBreakMenu() {
  setBackground(ST7735_BLACK);
  drawText("Pomodoro", title);
  drawText("Click to start/stop timer", subtitle);
}

void showBreakTimer() {
  drawText("Pomodoro", title);
  drawText("Click to start/stop timer", subtitle);
  drawText(String(breakLength).c_str(), time);
}

void setup() {
  Serial.begin(9600);

  // Set up text types
  title.x = tftWidth / 2;
  title.y = 0;
  title.size = 2;
  title.horizontalAnchor = "center";

  subtitle.x = tftWidth / 2;
  subtitle.y = 20;
  subtitle.size = 1.7;
  subtitle.horizontalAnchor = "center";

  time.x = tftWidth / 2;
  time.y = tftHeight - 10;
  time.size = 5;
  time.horizontalAnchor = "center";
  time.verticalAnchor = "bottom";

  initTFT();
  initRotEncoder();
  initBuzzer();

  setBackground(ST7735_BLACK);

  if (menu == "pomodoro") {
    showPomodoroMenu();
  } else {
    showBreakMenu();
  }
}

void loop() {
  if (digitalRead(ROT_KEY) == LOW) {
    timerStarted = !timerStarted;

    if (timerStarted) {
      if (menu == "pomodoro") {
        setBackground(ST7735_RED);
      } else {
        setBackground(ST7735_GREEN);
      }
    } else {
      setBackground(ST7735_BLACK);

      if (menu == "pomodoro") {
        showPomodoroMenu();
      } else {
        showBreakMenu();
      }
    }
  }

  if (timerStarted) {
    if (menu == "pomodoro") {
      showPomodoroTimer();
    } else {
      showBreakTimer();
    }
  }
}
