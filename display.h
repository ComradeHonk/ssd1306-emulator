/**
 * This Library was inspired by an SSD1306 OLED display library written
 * by Aleksander Alekseev (afiskon).
 *
 * https://github.com/afiskon/stm32-ssd1306
 */

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdint.h>

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

// Enumeration for screen colors
typedef enum {
  Black = 0x00,  // Black color, '.' character
  White = 0x01   // White color, '@' character
} DISPLAY_COLOR;

typedef struct {
  uint8_t x;
  uint8_t y;
} DISPLAY_VERTEX;

// Virtual display
extern DISPLAY_COLOR display_Buffer[DISPLAY_WIDTH][DISPLAY_HEIGHT];

// Procedure definitions
void display_Fill(DISPLAY_COLOR color);
void display_UpdateScreen(void);
void display_DrawPixel(uint8_t x, uint8_t y, DISPLAY_COLOR color);
void display_Line(uint8_t x1,
                  uint8_t y1,
                  uint8_t x2,
                  uint8_t y2,
                  DISPLAY_COLOR color);
void display_Polyline(const DISPLAY_VERTEX* par_vertex,
                      uint16_t par_size,
                      DISPLAY_COLOR color);

#endif  // __DISPLAY_H__
