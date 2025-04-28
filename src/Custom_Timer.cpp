#include <Arduino.h>
#include <Custom_Timer.h>

class Custom_Timer {
    private: 
        float time;
        float startTime;
    public:
        float length;
        bool running;

        Custom_Timer(float x) {
            length = x;
            Reset();
        }

        void Start() {
            startTime = millis();
            time = length;
            running = true;
        }

        float GetTime() {
            time = length - startTime;
        }

        String GetFormattedTime() {
            const float totalSeconds = GetTime() / 1000;
            int minutes = (int) totalSeconds / 60;
            int seconds = (int) totalSeconds % 60;
            
            String timeString = String(minutes) + ":" + (seconds < 10 ? "0" + String(seconds) : String(seconds));
            return timeString;
        }

        void Reset() {
            time = length;
            startTime = 0;
            running = false;
        }
};