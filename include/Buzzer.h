#ifndef Buzzer_h
#define Buzzer_h

#include <Arduino.h>

void initBuzzer();
void playNote(const int freq, const int dur);
void stop();

#endif