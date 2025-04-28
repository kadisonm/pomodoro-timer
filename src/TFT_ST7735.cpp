#include "TFT_ST7735.h"

// SCK = 13 and SDA == 11 (built in)

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
uint16_t currentBackgroundColor = ST7735_BLACK;

TextProperties title;
TextProperties subtitle;
TextProperties time;

String previousText;

void initTFT() {
    tft.initR(INITR_BLACKTAB);
    tft.setRotation(3);

    title.x = tftWidth / 2;
    title.y = 5;
    title.size = 2;
    title.horizontalAnchor = "center";

    subtitle.x = tftWidth / 2;
    subtitle.y = tftHeight - 5;
    subtitle.size = 1.7;
    subtitle.horizontalAnchor = "center";
    subtitle.verticalAnchor = "bottom";

    time.x = tftWidth / 2;
    time.y = tftHeight / 2;
    time.size = 4.9;
    time.horizontalAnchor = "center";
    time.verticalAnchor = "center";
}

void setBackground(uint16_t color) {
    currentBackgroundColor = color;
    tft.fillScreen(color);
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
    previousText = text;
}

void clearText(const char* text, TextProperties properties) {
    properties.color = currentBackgroundColor;

    drawText(text, properties);
}

void clearArea(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
    tft.fillRect(x, y, w, h, currentBackgroundColor);
}
