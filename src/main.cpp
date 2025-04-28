#include <Arduino.h>

#include <TFT_ST7735.h>
#include <Rotary_Encoder.h>
#include <Buzzer.h>
#include <Custom_Timer.h>

Custom_Timer pomodoroTimer = Custom_Timer(15 * 60000);
Custom_Timer breakTimer = Custom_Timer(5 * 60000);

// State management

enum State {
  Pomodoro,
  Break,
};

State currentState;

void changeState(State newState);

void PomodoroStart() {
  setBackground(ST7735_BLACK);
  drawText("Pomodoro", title);
  drawText("Click to start/stop timer", subtitle);
  pomodoroTimer.Reset();
}

void PomodoroLoop() {
  if (isButtonDown()) {
    if (!pomodoroTimer.running) {
      setBackground(ST7735_RED);
      drawText("Pomodoro", title);
      drawText("Click to start/stop timer", subtitle);
      pomodoroTimer.Start();
    } else {
      pomodoroTimer.Reset();
    }
  }

  if (pomodoroTimer.running) {
    clearArea(0, 60, tftWidth, tftHeight);
    drawText(pomodoroTimer.GetFormattedTime().c_str(), time);

    if (pomodoroTimer.GetTime() <= 0) {
      changeState(Break);
    }
  }
}

void BreakStart() {
  setBackground(ST7735_BLACK);
  drawText("Break", title);
  drawText("Click to start/stop timer", subtitle);
}

void BreakLoop() {
  if (isButtonDown()) {
    changeState(Pomodoro);
  }
}

void changeState(State newState) {
  currentState = newState;

  switch (currentState)
  {
    case Pomodoro:
      PomodoroStart();
      break;
    
    case Break:
      BreakStart();
      break;
  }
}

// Arduino

void setup() {
  Serial.begin(9600);

  initTFT();
  initRotEncoder();
  initBuzzer();

  setBackground(ST7735_BLACK);

  changeState(Pomodoro);
}

void loop() {
  switch (currentState)
  {
    case Pomodoro:
      PomodoroLoop();
      break;
    
    case Break:
      BreakLoop();
      break;
  }
}
