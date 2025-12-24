# ssd1306-emulator
Library for emulating the SSD1306 OLED display in the terminal, based on [stm32-ssd1306](https://github.com/afiskon/stm32-ssd1306).

It works by printing the screenbuffer to the terminal using pairs of characters (to achieve the correct aspect ratio):
- '██' for white pixels
- spaces for black pixels

A frame is added to show screen boundaries.

It uses partial redraw (draws only changed pixels) to conserve resources and improve performance.

> [!NOTE]
> Rendering performance may vary between terminal emulators. While Linux terminals can comfortably draw at 2000+ FPS,
on Windows it's common to have around 3-6 FPS due to Windows console being really slow and inefficient.

In addition to functions available in the [original library](https://github.com/afiskon/stm32-ssd1306),
it offers PC implementations of `HAL_GetTick` and `HAL_Delay` which might be useful for writing code
that can be copied-and-pasted into an STM32 project.

## Usage

> [!IMPORTANT]
> By default screen size is 128x64. Rendering is done with Unicode characters, so to see the effects
you'll need to set a very small terminal font size (and have Unicode support, obviously 😉).

This is a small example of how to use the library:
```c
// Include the header file
#include "path/to/library/ssd1306-emulator/ssd1306.h"

int main() {
  // Initialize the screen
  ssd1306_Init();

  // Draw a filled in 20x20 square
  ssd1306_FillRectangle(10, 10, 30, 30, White);

  // Update the screen. You need to call this to make changes appear on screen
  ssd1306_UpdateScreen();

  return 0;
}
```
Compile and run the program:
```
gcc path/to/program.c path/to/library/ssd1306-emulator/ssd1306.c -lm && ./a.out
```
You should see the square appear in the terminal:
<img width="1397" height="805" alt="image" src="https://github.com/user-attachments/assets/a94ebefb-95fa-48a0-9f7b-6c97ffe93c15" />

### Headers

| Header | Contents |
|--------|----------|
| [`ssd1306.h`](ssd1306.h) | Main header file. Contains all API functions |
| [`ssd1306_conf.h`](ssd1306_conf.h) | Screen configuration and enabled fonts |
| [`ssd1306_fonts.h`](ssd1306_fonts.h) | Fonts for writing text to the screen |
| [`ssd1306_tests.h`](ssd1306_tests.h) | Various tests for exploring functionality and learning |

## Supported platforms

Theoretically, anything that can compile C and run a terminal session could work, but the main target are PC operating systems:

| Platform | Status |
|----------|--------|
| **Linux/Unix** | Fully supported |
| **Windows** | Fully supported |
| **macOS** | Supported, not tested |

## Testing

Functionality can be tested by compiling the program [`test_all.c`](test_all.c) included in this repository:
```
git clone https://github.com/ComradeHonk/ssd1306-emulator.git
cd ssd1306-emulator
gcc test_all.c ssd1306.c ssd1306_tests.c ssd1306_fonts.c -lm
```
and running it with:
```
./a.out
```
This should be the output:

https://github.com/user-attachments/assets/0cb9d1fb-1a29-4290-ba17-70d979b41b8e

## API Reference

```c
// Screen management
void ssd1306_Init(void);
void ssd1306_Fill(SSD1306_COLOR color);
void ssd1306_UpdateScreen(void);
void ssd1306_SetCursor(uint8_t x, uint8_t y);

// Drawing
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);

// Characters
char ssd1306_WriteChar(char ch, SSD1306_Font_t Font, SSD1306_COLOR color);
char ssd1306_WriteString(char* str, SSD1306_Font_t Font, SSD1306_COLOR color);

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

// HAL replacements
uint32_t HAL_GetTick(void);
void HAL_Delay(uint32_t Delay);
```

All above functions have more detailed documentation included with their declarations in [`ssd1306.h`](ssd1306.h).

## Configuration

Configuration is done by editing the contents of [`ssd1306_conf.h`](ssd1306_conf.h).

### Screen resolution
The original library is made to work with SSD1306, SH1106, SH1107 and SSD1309 OLED displays as they are compatible with each other.
This emulator isn't limited to any particular set of devices as it doesn't interface with real hardware, so it can be configured for any
screen resolution:
```c
// The width of the screen can be set using this
// define. The default value is 128
#define SSD1306_WIDTH 128

// The height can be changed as well if necessary.
// The default value is 64
#define SSD1306_HEIGHT 64
```

### Fonts
There are a number of fonts included with the library. Their use can be toggled with `#define`:
```c
// Include all fonts by default
#define SSD1306_INCLUDE_FONT_6x8
#define SSD1306_INCLUDE_FONT_7x10
#define SSD1306_INCLUDE_FONT_11x18
#define SSD1306_INCLUDE_FONT_16x26

#define SSD1306_INCLUDE_FONT_16x24

#define SSD1306_INCLUDE_FONT_16x15
```

If you wish to use custom fonts, see [this example](https://github.com/afiskon/stm32-ssd1306/tree/master/examples/custom-fonts) in the original library repo.

## Credits

Thanks to [Wydział Wewnętrzny](https://github.com/WW5833) for helping with optimization and Windows testing.

Based on [STM32 SSD1306 library](https://github.com/afiskon/stm32-ssd1306) written by Aleksander Alekseev (afiskon)
