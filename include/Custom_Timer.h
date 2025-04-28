#ifndef Custom_Timer_h
#define Custom_Timer_h

#include <Arduino.h>

class Custom_Timer {
    private: 
        float time;
        float startTime;
    public:
        float length;
        bool running;
        Custom_Timer(float x);
        void Start();
        float GetTime();
        String GetFormattedTime();
        void Reset();
};

#endif