/**
 * This Library was inspired by an SSD1306 OLED ssd1306 library written
 * by Aleksander Alekseev (afiskon).
 *
 * https://github.com/afiskon/stm32-ssd1306
 */

#ifndef __SSD1306_H__
#define __SSD1306_H__

#include <stdint.h>

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

// Enumeration for screen colors
typedef enum {
  Black = 0x00,  // Black color, ' ' character
  White = 0x01  // Pixel is set, '█' character. Color can be altered with escape
                // codes or terminal configuration
} SSD1306_COLOR;

typedef struct {
  uint8_t x;
  uint8_t y;
} SSD1306_VERTEX;

// Screenbuffer
extern SSD1306_COLOR SSD1306_Buffer[SSD1306_WIDTH][SSD1306_HEIGHT];

// Procedure definitions
void ssd1306_Fill(SSD1306_COLOR color);
void ssd1306_UpdateScreen(void);
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
void ssd1306_Line(uint8_t x1,
                  uint8_t y1,
                  uint8_t x2,
                  uint8_t y2,
                  SSD1306_COLOR color);
void ssd1306_Polyline(const SSD1306_VERTEX* par_vertex,
                      uint16_t par_size,
                      SSD1306_COLOR color);

#endif  // __SSD1306_H__
