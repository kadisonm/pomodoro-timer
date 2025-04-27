#include <Buzzer.h>

const int BUZZER = 7;

void initBuzzer() {
    pinMode(BUZZER, OUTPUT);
}

void playNote(const int freq, const int dur) {
    tone(BUZZER, freq, dur);
    delay(dur * 1.30);
}

void stop() {
    noTone(BUZZER);
}