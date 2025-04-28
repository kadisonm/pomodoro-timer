#include <Arduino.h>

#include <TFT_ST7735.h>
#include <Rotary_Encoder.h>
#include <Buzzer.h>
#include <State.h>

TextProperties title;
TextProperties subtitle;
TextProperties time;

boolean timerStarted = false;

int pomodoroLength = 15;
int breakLength = 5;

unsigned long timer = 0;
unsigned long startTime = 0;

unsigned long debounce = 0;

class PomodoroScreen : public State {
  public:
    void start() {

    }

    void update() {

    }
};


class BreakScreen : public State {
  public:
    void start() {

    }

    void update() {

    }
};

PomodoroScreen pomodoroState = PomodoroScreen();
BreakScreen breakState = BreakScreen();

State state = pomodoroState;

void drawPomodoroMenu() {
  drawText("Pomodoro", title);
  drawText("Click to start/stop timer", subtitle);
}

void drawBreakMenu() {
  drawText("Break", title);
  drawText("Click to start/stop timer", subtitle);
}

void changeState(String newState) {
  state = newState;
  timerStarted = false;

  setBackground(ST7735_BLACK);
  
  if (newState == "Pomodoro") {
    drawPomodoroMenu();
    timer = pomodoroLength * 60000;
  } else {
    drawBreakMenu();
    timer = breakLength * 60000;
  }
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

  changeState("pomodoro");
}

void rotEncoderPulsed(int direction) {
  Serial.print(direction);
  if (!timerStarted) {
    if (state == "pomodoro") {
      breakLength += direction;
      timer = pomodoroLength * 60000;
    } else {
      breakLength += direction;
      timer = breakLength * 60000;
    }
  }
}

void loop() {
  if (isButtonDown() && millis() - debounce > 5000) {
    debounce = millis();
    timerStarted = !timerStarted;

    if (timerStarted) {
      startTime = millis();

      if (state == "pomodoro") {
        setBackground(ST7735_RED);
        drawPomodoroMenu();
      } else {
        setBackground(ST7735_GREEN);
        drawBreakMenu();
      }
    }
  }

  clearText(String(timer / 60000).c_str(), time);

  if (timerStarted) {
    startTime += millis();
    timer -= startTime;
  }

  drawText(String(timer / 60000).c_str(), time);
}
