#ifndef TFT_h
#define TFT_h

#include <Adafruit_ST7735.h>

extern Adafruit_ST7735 tft;
extern int16_t tftWidth;
extern int16_t tftHeight;

extern String previousText;

struct TextProperties {
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t size = 1;
    uint16_t color = ST7735_WHITE;
    String horizontalAnchor = "left";
    String verticalAnchor = "top";
    boolean textWrap = false;
};

extern TextProperties title;
extern TextProperties subtitle;
extern TextProperties time;

void initTFT();
void setBackground(uint16_t color);
void drawText(const char* text, const TextProperties properties);
void clearText(const char* text, const TextProperties properties);
void clearArea(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

#endif