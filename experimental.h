#ifndef __EXPERIMENTAL_H__
#define __EXPERIMENTAL_H__

#include "ssd1306.h"
#include "stdint.h"

void octantrenderer_UpdateScreen(
    uint8_t SSD1306_Buffer[SSD1306_BUFFER_SIZE], uint8_t SSD1306_TerminalBuffer[SSD1306_BUFFER_SIZE]
);

#endif // __EXPERIMENTAL_H__
