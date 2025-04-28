#ifndef Custom_Timer_h
#define Custom_Timer_h

#include <Arduino.h>

class Custom_Timer {    
    public:
        unsigned long time; 
        unsigned long length;
        bool paused;
        Custom_Timer(unsigned long x);
        void Play();
        String GetFormattedTime();
        void IncreaseLength(int direction);
        void Update();
        void Pause();
        void Reset();
};

#endif