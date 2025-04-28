#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include <Arduino.h>

extern int ROT_KEY; 
extern int rotCounter;

void initRotEncoder();
void updateRotEncoder();
bool isButtonDown();
int checkRotation();

#endif