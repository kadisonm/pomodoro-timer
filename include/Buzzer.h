#ifndef Buzzer
#define Buzzer

#include <Arduino.h>

void initBuzzer();
void playNote(const int freq, const int dur);
void stop();

#endif