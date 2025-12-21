#include "ssd1306.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

SSD1306_COLOR SSD1306_Buffer[SSD1306_WIDTH][SSD1306_HEIGHT] = {0};

// Clear the terminal
static void clear_screen(void) {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Fill the whole screen with the given color
void ssd1306_Fill(SSD1306_COLOR color) {
  for (uint16_t y = 0; y < SSD1306_HEIGHT; ++y)
    for (uint16_t x = 0; x < SSD1306_WIDTH; ++x)
      SSD1306_Buffer[x][y] = color;
}

// Write the terminal with changes to the screen
void ssd1306_UpdateScreen(void) {
  // Clear screen before printing
  clear_screen();

  // Top border
  printf("╔");
  for (uint16_t x = 0; x < SSD1306_WIDTH; ++x)
    printf("═");
  printf("╗\n");

  // '█' - White, ' ' - Black
  for (uint16_t y = 0; y < SSD1306_HEIGHT; ++y) {
    printf("║");  // Left border
    for (uint16_t x = 0; x < SSD1306_WIDTH; ++x)
      if (SSD1306_Buffer[x][y] == White)
        printf("█");
      else
        printf(" ");
    printf("║\n");  // Right border
  }

  // Bottom border
  printf("╚");
  for (uint16_t x = 0; x < SSD1306_WIDTH; ++x)
    printf("═");
  printf("╝\n");
}

/*
 * Draw one pixel in the screenbuffer
 * X => X Coordinate
 * Y => Y Coordinate
 * color => Pixel color
 */
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color) {
  if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
    return;

  SSD1306_Buffer[x][y] = color;
}

// Draw line by Bresenhem's algorithm
void ssd1306_Line(uint8_t x1,
                  uint8_t y1,
                  uint8_t x2,
                  uint8_t y2,
                  SSD1306_COLOR color) {
  int32_t deltaX = abs(x2 - x1);
  int32_t deltaY = abs(y2 - y1);
  int32_t signX = ((x1 < x2) ? 1 : -1);
  int32_t signY = ((y1 < y2) ? 1 : -1);
  int32_t error = deltaX - deltaY;
  int32_t error2;

  ssd1306_DrawPixel(x2, y2, color);

  while ((x1 != x2) || (y1 != y2)) {
    ssd1306_DrawPixel(x1, y1, color);
    error2 = error * 2;
    if (error2 > -deltaY) {
      error -= deltaY;
      x1 += signX;
    }

    if (error2 < deltaX) {
      error += deltaX;
      y1 += signY;
    }
  }
  return;
}

// Draw polyline using pointer array of vertices
void ssd1306_Polyline(const SSD1306_VERTEX* par_vertex,
                      uint16_t par_size,
                      SSD1306_COLOR color) {
  if (par_vertex == NULL)
    return;

  for (uint16_t i = 1; i < par_size; i++)
    ssd1306_Line(par_vertex[i - 1].x, par_vertex[i - 1].y, par_vertex[i].x,
                 par_vertex[i].y, color);
}
