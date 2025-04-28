#include <Arduino.h>

#include <TFT_ST7735.h>
#include <Rotary_Encoder.h>
#include <Buzzer.h>
#include <Custom_Timer.h>

Custom_Timer pomodoroTimer = Custom_Timer(.2 * 60000);
Custom_Timer breakTimer = Custom_Timer(.1 * 60000);

unsigned long lastUpdate = millis();

enum State {
  Pomodoro,
  Break,
};

State currentState;

void changeState(State newState) {
  currentState = newState;

  if (currentState == Pomodoro) {
    setBackground(0x602805);
    drawText("Pomodoro", title);
    drawText("Click to start timer", subtitle);
    pomodoroTimer.Reset();
    drawText(pomodoroTimer.GetFormattedTime().c_str(), time);
  } else {
    setBackground(0x223D4F);
    drawText("Break", title);
    drawText("Click to start timer", subtitle);
    breakTimer.Reset();
    drawText(breakTimer.GetFormattedTime().c_str(), time);
  }
}

// Arduino

void setup() {
  Serial.begin(9600);

  initTFT();
  initRotEncoder();
  initBuzzer();

  changeState(Pomodoro);
}

void loop() {
  if (isButtonDown()) {
    if (currentState == Pomodoro) {
      if (pomodoroTimer.paused) {
        setBackground(0xC55C5C);
        drawText("Pomodoro", title);
        drawText("Click to pause timer", subtitle);
        drawText(pomodoroTimer.GetFormattedTime().c_str(), time);
        pomodoroTimer.Play();
      } else {
        pomodoroTimer.Pause();
        setBackground(0x602805);
        drawText("Pomodoro", title);
        drawText("Click to play timer", subtitle);
        drawText(pomodoroTimer.GetFormattedTime().c_str(), time);
      }  
    } else {
      if (breakTimer.paused) {
        setBackground(0x2E5F7F);
        drawText("Break", title);
        drawText("Click to pause timer", subtitle);
        drawText(breakTimer.GetFormattedTime().c_str(), time);
        breakTimer.Play();
      } else {
        breakTimer.Pause();
        setBackground(0x223D4F);
        drawText("Break", title);
        drawText("Click to play timer", subtitle);
        drawText(breakTimer.GetFormattedTime().c_str(), time);
      }  
    }
  }
  
  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();
    pomodoroTimer.Update();
    breakTimer.Update();

    if (currentState == Pomodoro) {
      if (!pomodoroTimer.paused) {
        if (pomodoroTimer.time <= 0) {
          changeState(Break);
          return;
        }

        clearText(previousText.c_str(), time);
        drawText(pomodoroTimer.GetFormattedTime().c_str(), time);  
      }
    } else {
      if (!breakTimer.paused) {
        if (breakTimer.time <= 0) {
          changeState(Pomodoro);
          return;
        }

        clearText(previousText.c_str(), time);
        drawText(breakTimer.GetFormattedTime().c_str(), time);
      }
    }
  }
}
