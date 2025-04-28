#include <Arduino.h>
#include <Custom_Timer.h>

const unsigned long maxTimerLength = 3540000;

Custom_Timer::Custom_Timer(unsigned long x) {
    length = x;
    Reset();
}

void Custom_Timer::Play() {
    paused = false;
}

String Custom_Timer::GetFormattedTime() {
    const float totalSeconds = time / 1000;
    int minutes = (int) totalSeconds / 60;
    int seconds = (int) totalSeconds % 60;
    
    String timeString = (minutes < 10 ? "0" + String(minutes) : String(minutes)) + ":" + (seconds < 10 ? "0" + String(seconds) : String(seconds));
    return timeString;
}

void Custom_Timer::Update() {
    if (!paused && time > 0) {
        time -= 1000;
    }
}

void Custom_Timer::IncreaseLength(int direction) {
    if (direction == -1 && time <= 60000) {
        return;
    } 

    unsigned long newTime = constrain(time + (60000UL * direction), 0UL, maxTimerLength);
    time = newTime;
    length = newTime;
}

void Custom_Timer::Pause() {
    paused = true;
}

void Custom_Timer::Reset() {
    time = length;
    paused = true;
}