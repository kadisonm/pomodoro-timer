#include "TFT_ST7735.h"

// TFT PINS:
// LED (CONNECT TO 3.3V)
// SCK
// SDA
// AO
// RESET
// CS
// GND
// VCC

const int TFT_CS = 8; // Clock Signal
const int TFT_RESET = 9;
const int TFT_AO = 10; // Data command

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_AO, TFT_RESET);

Adafruit_ST7735 getDisplay() {
    return tft;
}

void drawText(const char* text, TextProperties properties) {
    tft.setTextSize(properties.size);
    tft.setTextColor(properties.color);

    int16_t cursorX, cursorY = 0;

    int16_t x1, y1;
    uint16_t w, h;
    tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

    // Aligns
    if (properties.horizontalAlign == "center") {
        cursorX = properties.x - (w / 2);
    } else if (properties.horizontalAlign == "right") {
        cursorX = properties.x - w;
    }

    if (properties.verticalAlign == "center") {
        cursorY = properties.y - (h / 2);
    } else if (properties.verticalAlign == "bottom") {
        cursorY = properties.y - h;
    }

    tft.setCursor(cursorX, cursorY);

    tft.println(text);
}

