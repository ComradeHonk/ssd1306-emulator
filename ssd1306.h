/**
 * This Library is based on SSD1306 OLED display library written
 * by Aleksander Alekseev (afiskon).
 *
 * https://github.com/afiskon/stm32-ssd1306
 */

#ifndef __SSD1306_H__
#define __SSD1306_H__

#include "ssd1306_conf.h"
#include <stdint.h>

#define SSD1306_BUFFER_SIZE (SSD1306_WIDTH * SSD1306_HEIGHT / 8)

// Enumeration for screen colors
typedef enum {
  Black = 0x00, // Black color, ' ' character
  White = 0x01  // Pixel is set, '█' character. Color can be altered with escape
                // codes or terminal configuration
} SSD1306_COLOR;

typedef enum {
  SSD1306_OK = 0x00,
  SSD1306_ERR = 0x01 // Generic error
} SSD1306_Error_t;

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

// Screen management
/**
 * @brief Initialize the screen and terminal with defaults
 */
void ssd1306_Init(void);

/**
 * @brief Fill the whole screen with the given color
 *
 * @param color Color to fill the screen with
 */
void ssd1306_Fill(SSD1306_COLOR color);

/**
 * @brief Write the terminal with changes to the screen
 * Uses partial redraw for best performance
 */
void ssd1306_UpdateScreen(void);

/**
 * @brief Position the cursor
 *
 * @param x X Coordinate of new cursor position
 * @param y Y Coordinate of new cursor position
 */
void ssd1306_SetCursor(uint8_t x, uint8_t y);

// Drawing
/**
 * @brief Draw one pixel to the screenbuffer
 *
 * @param x X Coordinate of the pixel
 * @param y Y Coordinate of the pixel
 * @param color Color of the pixel
 */
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);

// Characters
/**
 * @brief Draw 1 char to the screen
 *
 * @param ch Character to draw
 * @param Font Font to use when drawing
 * @param color Color of the character
 * @return char Drawn character on success, 0 on failure (invalid character or no space)
 */
char ssd1306_WriteChar(char ch, SSD1306_Font_t Font, SSD1306_COLOR color);

/**
 * @brief Write full string to screenbuffer
 *
 * @param str String to write
 * @param Font Font to use when writing
 * @param color Color of the string
 * @return char Null terminator '\0' on success, string character on failure
 * Returned character signals where the failure occured
 */
char ssd1306_WriteString(char* str, SSD1306_Font_t Font, SSD1306_COLOR color);

// Lines
/**
 * @brief Draw line by Bresenham's algorithm
 *
 * @param x1 X Coordinate of the start point
 * @param y1 Y Coordinate of the start point
 * @param x2 X Coordinate of the end point
 * @param y2 Y Coordinate of the end point
 * @param color Color of line
 */
void ssd1306_Line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);

/**
 * @brief Draw polyline using pointer array of vertices
 *
 * @param par_vertex Array of vertices to join with lines
 * @param par_size Size of vertex array
 * @param color Color of polyline
 */
void ssd1306_Polyline(const SSD1306_VERTEX* par_vertex, uint16_t par_size, SSD1306_COLOR color);

// Rectangles
/**
 * @brief Draw a rectangle
 *
 * @param x1 X Coordinate of top left corner
 * @param y1 Y Coordinate of top left corner
 * @param x2 X Coordinate of bottom right corner
 * @param y2 Y Coordinate of bottom right corner
 * @param color Color of the rectangle
 */
void ssd1306_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);

/**
 * @brief Draw a filled rectangle
 *
 * @param x1 X Coordinate of top left corner
 * @param y1 Y Coordinate of top left corner
 * @param x2 X Coordinate of bottom right corner
 * @param y2 Y Coordinate of bottom right corner
 * @param color Color of the rectangle
 */
void ssd1306_FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);

/**
 * @brief Invert color of pixels in rectangle (include border)
 *
 * @param x1 X Coordinate of top left corner (must not be greater than x2)
 * @param y1 Y Coordinate of top left corner (must not be greater than y2)
 * @param x2 X Coordinate of bottom right corner
 * @param y2 Y Coordinate of bottom right corner
 * @return SSD1306_Error_t SSD1306_OK on success, SSD1306_ERR on invalid coordinates
 */
SSD1306_Error_t ssd1306_InvertRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

// Arcs
/**
 * @brief Draw an arc
 * Angle is beginning from the 4th quart of trigonometric circle (3pi/2)
 *
 * @param x X Coordinate of the center point
 * @param y Y Coordinate of the center point
 * @param radius Radius of the arc
 * @param start_angle Start angle in degrees
 * @param sweep End angle in degrees
 * @param color Color of the arc
 */
void ssd1306_DrawArc(
    uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR color
);

/**
 * @brief Draw an arc with radius lines
 * Angle is beginning from the 4th quart of trigonometric circle (3pi/2)
 *
 * @param x X Coordinate of the center point
 * @param y Y Coordinate of the center point
 * @param radius Radius of the arc
 * @param start_angle Start angle in degrees
 * @param sweep End angle in degrees
 * @param color Color of the arc
 */
void ssd1306_DrawArcWithRadiusLine(
    uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR color
);

// Circles
/**
 * @brief Draw circle by Bresenham's algorithm
 *
 * @param par_x X Coordinate of the center point
 * @param par_y Y Coordinate of the center point
 * @param par_r Radius of the circle
 * @param color Color of the circle
 */
void ssd1306_DrawCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r, SSD1306_COLOR color);

/**
 * @brief Draw filled circle. Pixel positions calculated using Bresenham's algorithm
 *
 * @param par_x X Coordinate of the center point
 * @param par_y Y Coordinate of the center point
 * @param par_r Radius of the circle
 * @param color Color of the circle
 */
void ssd1306_FillCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r, SSD1306_COLOR par_color);

// Bitmaps
/**
 * @brief Draw a bitmap
 *
 * @param x X Coordinate of top left corner of the bitmap
 * @param y Y Coordinate of top left corner of the bitmap
 * @param bitmap Bitmap to draw
 * @param w Width of the bitmap
 * @param h Height of the bitmap
 * @param color Color of the bitmap
 */
void ssd1306_DrawBitmap(
    uint8_t x, uint8_t y, const unsigned char* bitmap, uint8_t w, uint8_t h, SSD1306_COLOR color
);

// HAL replacements
/**
 * @brief Get number of ticks elapsed since the start
 *
 * @return uint32_t Ticks elapsed since the start
 */
uint32_t HAL_GetTick(void);

/**
 * @brief Create a delay
 *
 * @param Delay Delay in milliseconds
 */
void HAL_Delay(uint32_t Delay);

#endif // __SSD1306_H__
