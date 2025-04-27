#include <Rotary_Encoder.h>

const int ROT_S1 = 3;
const int ROT_S2 = 4;

int s2State;
int lastS2State;

int ROT_KEY = 5; 
int rotCounter = 0;

const unsigned long dbDelay = 50;
unsigned long lastDb = 0;

void initRotEncoder() {
    pinMode(ROT_KEY, INPUT_PULLUP);
    pinMode(ROT_S1, INPUT);
    pinMode(ROT_S2, INPUT);
    attachInterrupt(digitalPinToInterrupt(ROT_S1), updateRotEncoder, CHANGE);
}

void updateRotEncoder() {
    s2State = digitalRead(ROT_S2);

    // Pulse occured
    if (s2State == HIGH && lastS2State == LOW){     
        // Anti-clockwise
        if (digitalRead(ROT_S1) == HIGH) { 
            rotCounter++;
        } else {
            rotCounter--;
        }
    } 

    lastS2State = s2State;
}

boolean isButtonDown() {
    int reading = digitalRead(ROT_KEY);

    if (reading == LOW && (millis() - lastDb) > dbDelay) {
        lastDb = millis();
        return true;
    }

    return false;
}