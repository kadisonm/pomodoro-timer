#ifndef TFT
#define TFT

#include <Adafruit_ST7735.h>

extern Adafruit_ST7735 tft;
extern int16_t tftWidth;
extern int16_t tftHeight;

struct TextProperties {
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t size = 1;
    uint16_t color = ST7735_WHITE;
    String horizontalAnchor = "left";
    String verticalAnchor = "top";
    boolean textWrap = false;
};

void initTFT();
void drawText(const char* text, const TextProperties properties);

#endif