/**
 * This Library was inspired by an SSD1306 OLED display library written
 * by Aleksander Alekseev (afiskon).
 *
 * https://github.com/afiskon/stm32-ssd1306
 */

#ifndef __SSD1306_H__
#define __SSD1306_H__

#include <stdint.h>

#define SSD1306_HEIGHT 64
#define SSD1306_WIDTH 128

// Enumeration for screen colors
typedef enum {
  Black = 0x00, // Black color, ' ' character
  White = 0x01  // Pixel is set, '█' character. Color can be altered with escape
                // codes or terminal configuration
} SSD1306_COLOR;

// Struct to store transformations
typedef struct {
  uint16_t CurrentX;
  uint16_t CurrentY;
  uint8_t Initialized;
} SSD1306_t;

typedef struct {
  uint8_t x;
  uint8_t y;
} SSD1306_VERTEX;

// Font
typedef struct {
  const uint8_t width;             // Font width in pixels
  const uint8_t height;            // Font height in pixels
  const uint16_t* const data;      // Pointer to font data array
  const uint8_t* const char_width; // Proportional character width in pixels
                                   // (NULL for monospaced)
} SSD1306_Font_t;

// Procedure definitions
void ssd1306_Init(void);
void ssd1306_Fill(SSD1306_COLOR color);
void ssd1306_UpdateScreen(void);
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
char ssd1306_WriteChar(char ch, SSD1306_Font_t Font, SSD1306_COLOR color);
char ssd1306_WriteString(char* str, SSD1306_Font_t Font, SSD1306_COLOR color);
void ssd1306_SetCursor(uint8_t x, uint8_t y);
void ssd1306_Line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
void ssd1306_DrawArc(
    uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR color
);
void ssd1306_DrawArcWithRadiusLine(
    uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR color
);
void ssd1306_DrawCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r, SSD1306_COLOR color);
void ssd1306_FillCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r, SSD1306_COLOR par_color);
void ssd1306_Polyline(const SSD1306_VERTEX* par_vertex, uint16_t par_size, SSD1306_COLOR color);
void ssd1306_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
void ssd1306_FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
void ssd1306_DrawBitmap(
    uint8_t x, uint8_t y, const unsigned char* bitmap, uint8_t w, uint8_t h, SSD1306_COLOR color
);

#endif // __SSD1306_H__
