#ifndef RotaryEncoder
#define RotaryEncoder

#include <Arduino.h>

extern int ROT_KEY; 
extern int rotCounter;

void initRotEncoder();
void updateRotEncoder();
boolean isButtonDown();
void rotEncoderPulsed(int direction);

#endif