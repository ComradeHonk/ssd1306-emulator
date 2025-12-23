# ssd1306-emulator
Library for emulating the SSD1306 OLED display in the terminal.

## Usage

> [!IMPORTANT]
> By default screen size is 128x64. Rendering is done with Unicode characters, so to see the effects
you'll need to set a very small terminal font size (and have Unicode support, obviously 😉).

Functionality can be tested by compiling test program `test_all.c` with the following command:
```
gcc test_all.c ssd1306.c ssd1306_tests.c ssd1306_fonts.c -lm
```
or with `clang`:
```
clang test_all.c ssd1306.c ssd1306_tests.c ssd1306_fonts.c -lm
```

> [!NOTE]
> Rendering performance may vary between terminal emulators, especially on Windows.

[![Test showcase](https://img.youtube.com/vi/8STQJmwjz-Y/maxresdefault.jpg)](https://youtu.be/8STQJmwjz-Y)

## API Reference

```c
// Screen management
void ssd1306_Init(void);
void ssd1306_Fill(SSD1306_COLOR color);
void ssd1306_UpdateScreen(void);

// Drawing
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);

// Characters
char ssd1306_WriteChar(char ch, SSD1306_Font_t Font, SSD1306_COLOR color);
char ssd1306_WriteString(char* str, SSD1306_Font_t Font, SSD1306_COLOR color);
void ssd1306_SetCursor(uint8_t x, uint8_t y);

// Lines
void ssd1306_Line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
void ssd1306_Polyline(const SSD1306_VERTEX* par_vertex, uint16_t par_size, SSD1306_COLOR color);

// Rectangles
void ssd1306_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
void ssd1306_FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
SSD1306_Error_t ssd1306_InvertRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

// Arcs
void ssd1306_DrawArc(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR color);
void ssd1306_DrawArcWithRadiusLine(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR color);

// Circles
void ssd1306_DrawCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r, SSD1306_COLOR color);
void ssd1306_FillCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r, SSD1306_COLOR par_color);

// Bitmaps
void ssd1306_DrawBitmap(uint8_t x, uint8_t y, const unsigned char* bitmap, uint8_t w, uint8_t h, SSD1306_COLOR color);
```

## Credits

Based on [STM32 SSD1306 library](https://github.com/afiskon/stm32-ssd1306) written by Aleksander Alekseev (afiskon)
