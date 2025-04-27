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

int16_t tftWidth = tft.height();
int16_t tftHeight = tft.width();

void initTFT() {
    tft.initR(INITR_BLACKTAB);
    tft.setRotation(3);
}

void drawText(const char* text, TextProperties properties) {
    int16_t cursorX = properties.x;
    int16_t cursorY = properties.y;

    
    tft.setTextWrap(properties.textWrap);
    tft.setTextColor(properties.color);
    tft.setTextSize(properties.size);

    int16_t x1, y1;
    uint16_t w, h;
    tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

    // Aligns
    if (properties.horizontalAnchor == "center") {
        cursorX = properties.x - (w / 2);
    } else if (properties.horizontalAnchor == "right") {
        cursorX = properties.x - w;
    }

    if (properties.verticalAnchor == "center") {
        cursorY = properties.y - (h / 2);
    } else if (properties.verticalAnchor == "bottom") {
        cursorY = properties.y - h;
    }

    tft.setCursor(cursorX, cursorY);
    tft.print(text);
}

