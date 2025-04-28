#include <Rotary_Encoder.h>

const int ROT_S1 = 3;
const int ROT_S2 = 4;

int s2State;
int lastS2State;

int ROT_KEY = 5; 
int rotCounter = 0;
int oldCounter = 0;

unsigned long lastDb = 0;
unsigned long lastRotDb = 0;

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
        oldCounter = rotCounter;
        // Anti-clockwise
        if (digitalRead(ROT_S1) == HIGH) { 
            rotCounter--;
        } else {
            rotCounter++;
        }
    } 

    lastS2State = s2State;
}

bool isButtonDown() {
    int reading = digitalRead(ROT_KEY);

    if (reading == LOW && (millis() - lastDb) > 500) {
        lastDb = millis();
        return true;
    }

    return false;
}

int checkRotation() {
    if (rotCounter != oldCounter && (millis() - lastRotDb) > 100) {
        int direction = (rotCounter > oldCounter) ? 1 : -1;
        rotCounter = oldCounter;

        return direction;
    }

    return 0;
}