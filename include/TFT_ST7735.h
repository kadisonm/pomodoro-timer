#ifndef TFT
#define TFT

#include <Adafruit_ST7735.h>

extern Adafruit_ST7735 tft;

Adafruit_ST7735 getDisplay();

struct TextProperties {
    uint8_t size = 1;
    uint8_t x = 0;
    uint8_t y = 0;
    uint16_t color = ST7735_BLACK;
    String horizontalAlign = "left";
    String verticalAlign = "top";
};

void drawText(const char* text, const TextProperties properties);

#endif