#include <Arduino.h>

#include <TFT_ST7735.h>
#include <Rotary_Encoder.h>
#include <Buzzer.h>
#include <Custom_Timer.h>

Custom_Timer pomodoroTimer = Custom_Timer(25 * 60000);
Custom_Timer breakTimer = Custom_Timer(10 * 60000);

unsigned long lastUpdate = millis();


enum State {
  Pomodoro,
  Break,
};

State currentState;

void changeState(State newState) {
  currentState = newState;

  if (currentState == Pomodoro) {
    setBackground(ST7735_BLACK);
    drawText("Pomodoro", title);
    drawText("Click to start timer", subtitle);
    pomodoroTimer.Reset();
    drawText(pomodoroTimer.GetFormattedTime().c_str(), time);
  } else {
    setBackground(ST7735_BLACK);
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
        setBackground(ST7735_RED);
        drawText("Pomodoro", title);
        drawText("Click to pause timer", subtitle);
        drawText(pomodoroTimer.GetFormattedTime().c_str(), time);
        pomodoroTimer.Play();
      } else {
        pomodoroTimer.Pause();
        setBackground(ST7735_BLACK);
        drawText("Pomodoro", title);
        drawText("Click to resume timer", subtitle);
        drawText(pomodoroTimer.GetFormattedTime().c_str(), time);
      }  
    } else {
      if (breakTimer.paused) {
        setBackground(0x5c5c);
        drawText("Break", title);
        drawText("Click to pause timer", subtitle);
        drawText(breakTimer.GetFormattedTime().c_str(), time);
        breakTimer.Play();
      } else {
        breakTimer.Pause();
        setBackground(ST7735_BLACK);
        drawText("Break", title);
        drawText("Click to resume timer", subtitle);
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
          playNote(523, 200);
          playNote(659, 200);
          playNote(784, 300);
          changeState(Break);
          return;
        }

        clearText(previousText.c_str(), time);
        drawText(pomodoroTimer.GetFormattedTime().c_str(), time);  
      }
    } else {
      if (!breakTimer.paused) {
        if (breakTimer.time <= 0) {
          playNote(440, 200);
          playNote(392, 100);
          playNote(349, 300);
          changeState(Pomodoro);
          return;
        }

        clearText(previousText.c_str(), time);
        drawText(breakTimer.GetFormattedTime().c_str(), time);
      }
    }
  }

  const int direction = checkRotation();

  if (direction == 1 || direction == -1) {
    if (currentState == Pomodoro && pomodoroTimer.paused) {
        pomodoroTimer.IncreaseLength(direction);

        clearText(previousText.c_str(), time);
        drawText(pomodoroTimer.GetFormattedTime().c_str(), time);
      } else if (currentState == Break && breakTimer.paused) {
        breakTimer.IncreaseLength(direction);

        clearText(previousText.c_str(), time);
        drawText(breakTimer.GetFormattedTime().c_str(), time);
      }
    }      
  }

  
