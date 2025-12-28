#include "experimental.h"
#include "ssd1306.h"
#include "stdint.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static const char* octant_table[256] = {
    " ",    "𜺨", "𜺫", "🮂",    "𜴀", "▘",    "𜴁", "𜴂", "𜴃", "𜴄", "▝",    "𜴅",
    "𜴆", "𜴇", "𜴈", "▀",    "𜴉", "𜴊", "𜴋", "𜴌", "🯦", "𜴍", "𜴎", "𜴏",
    "𜴐", "𜴑", "𜴒", "𜴓", "𜴔", "𜴕", "𜴖", "𜴗", "𜴘", "𜴙", "𜴚", "𜴛",
    "𜴜", "𜴝", "𜴞", "𜴟", "🯧", "𜴠", "𜴡", "𜴢", "𜴣", "𜴤", "𜴥", "𜴦",
    "𜴧", "𜴨", "𜴩", "𜴪", "𜴫", "𜴬", "𜴭", "𜴮", "𜴯", "𜴰", "𜴱", "𜴲",
    "𜴳", "𜴴", "𜴵", "🮅",    "𜺣", "𜴶", "𜴷", "𜴸", "𜴹", "𜴺", "𜴻", "𜴼",
    "𜴽", "𜴾", "𜴿", "𜵀", "𜵁", "𜵂", "𜵃", "𜵄", "▖",    "𜵅", "𜵆", "𜵇",
    "𜵈", "▌",    "𜵉", "𜵊", "𜵋", "𜵌", "▞",    "𜵍", "𜵎", "𜵏", "𜵐", "▛",
    "𜵑", "𜵒", "𜵓", "𜵔", "𜵕", "𜵖", "𜵗", "𜵘", "𜵙", "𜵚", "𜵛", "𜵜",
    "𜵝", "𜵞", "𜵟", "𜵠", "𜵡", "𜵢", "𜵣", "𜵤", "𜵥", "𜵦", "𜵧", "𜵨",
    "𜵩", "𜵪", "𜵫", "𜵬", "𜵭", "𜵮", "𜵯", "𜵰", "𜺠", "𜵱", "𜵲", "𜵳",
    "𜵴", "𜵵", "𜵶", "𜵷", "𜵸", "𜵹", "𜵺", "𜵻", "𜵼", "𜵽", "𜵾", "𜵿",
    "𜶀", "𜶁", "𜶂", "𜶃", "𜶄", "𜶅", "𜶆", "𜶇", "𜶈", "𜶉", "𜶊", "𜶋",
    "𜶌", "𜶍", "𜶎", "𜶏", "▗",    "𜶐", "𜶑", "𜶒", "𜶓", "▚",    "𜶔", "𜶕",
    "𜶖", "𜶗", "▐",    "𜶘", "𜶙", "𜶚", "𜶛", "▜",    "𜶜", "𜶝", "𜶞", "𜶟",
    "𜶠", "𜶡", "𜶢", "𜶣", "𜶤", "𜶥", "𜶦", "𜶧", "𜶨", "𜶩", "𜶪", "𜶫",
    "▂",    "𜶬", "𜶭", "𜶮", "𜶯", "𜶰", "𜶱", "𜶲", "𜶳", "𜶴", "𜶵", "𜶶",
    "𜶷", "𜶸", "𜶹", "𜶺", "𜶻", "𜶼", "𜶽", "𜶾", "𜶿", "𜷀", "𜷁", "𜷂",
    "𜷃", "𜷄", "𜷅", "𜷆", "𜷇", "𜷈", "𜷉", "𜷊", "𜷋", "𜷌", "𜷍", "𜷎",
    "𜷏", "𜷐", "𜷑", "𜷒", "𜷓", "𜷔", "𜷕", "𜷖", "𜷗", "𜷘", "𜷙", "𜷚",
    "▄",    "𜷛", "𜷜", "𜷝", "𜷞", "▙",    "𜷟", "𜷠", "𜷡", "𜷢", "▟",    "𜷣",
    "▆",    "𜷤", "𜷥", "█",
};

void octantrenderer_UpdateScreen(
    uint8_t SSD1306_Buffer[SSD1306_BUFFER_SIZE], uint8_t SSD1306_TerminalBuffer[SSD1306_BUFFER_SIZE]
) {
  uint16_t x, y;

  static bool draw_start = true;
  if (draw_start) {
    // Print top border only at the start
    printf("╔");
    for (x = 0; x < SSD1306_WIDTH / 2; x++)
      printf("═");
    printf("╗\n");
  }

  // Skip over to handle 2x4 batches of pixels at once
  for (y = 0; y < SSD1306_HEIGHT - 3; y += 4) {
    if (draw_start)
      printf("║"); // Left border

    bool move_cursor = draw_start ? false : true;

    for (x = 0; x < SSD1306_WIDTH - 1; x += 2) {
      // Get 2x4 area of pixels
      size_t pixel_1_buffer_index = x + (y / 8) * SSD1306_WIDTH;
      size_t pixel_2_buffer_index = (x + 1) + (y / 8) * SSD1306_WIDTH;
      size_t pixel_3_buffer_index = x + ((y + 1) / 8) * SSD1306_WIDTH;
      size_t pixel_4_buffer_index = (x + 1) + ((y + 1) / 8) * SSD1306_WIDTH;
      size_t pixel_5_buffer_index = x + ((y + 2) / 8) * SSD1306_WIDTH;
      size_t pixel_6_buffer_index = (x + 1) + ((y + 2) / 8) * SSD1306_WIDTH;
      size_t pixel_7_buffer_index = x + ((y + 3) / 8) * SSD1306_WIDTH;
      size_t pixel_8_buffer_index = (x + 1) + ((y + 3) / 8) * SSD1306_WIDTH;

      uint8_t row_1_offset = 1 << (y % 8);
      uint8_t row_2_offset = 1 << ((y + 1) % 8);
      uint8_t row_3_offset = 1 << ((y + 2) % 8);
      uint8_t row_4_offset = 1 << ((y + 3) % 8);

      // If all pixels haven't changed, do not re-render them
      if (!draw_start &&
          !((SSD1306_Buffer[pixel_1_buffer_index] ^ SSD1306_TerminalBuffer[pixel_1_buffer_index]) &
            row_1_offset) &&
          !((SSD1306_Buffer[pixel_2_buffer_index] ^ SSD1306_TerminalBuffer[pixel_2_buffer_index]) &
            row_1_offset) &&
          !((SSD1306_Buffer[pixel_3_buffer_index] ^ SSD1306_TerminalBuffer[pixel_3_buffer_index]) &
            row_2_offset) &&
          !((SSD1306_Buffer[pixel_4_buffer_index] ^ SSD1306_TerminalBuffer[pixel_4_buffer_index]) &
            row_2_offset) &&
          !((SSD1306_Buffer[pixel_5_buffer_index] ^ SSD1306_TerminalBuffer[pixel_5_buffer_index]) &
            row_3_offset) &&
          !((SSD1306_Buffer[pixel_6_buffer_index] ^ SSD1306_TerminalBuffer[pixel_6_buffer_index]) &
            row_3_offset) &&
          !((SSD1306_Buffer[pixel_7_buffer_index] ^ SSD1306_TerminalBuffer[pixel_7_buffer_index]) &
            row_4_offset) &&
          !((SSD1306_Buffer[pixel_8_buffer_index] ^ SSD1306_TerminalBuffer[pixel_8_buffer_index]) &
            row_4_offset)) {
        move_cursor = true;
        continue;
      }

      // Synchronize buffers
      if (SSD1306_Buffer[pixel_1_buffer_index] & row_1_offset)
        SSD1306_TerminalBuffer[pixel_1_buffer_index] |= row_1_offset;
      else
        SSD1306_TerminalBuffer[pixel_1_buffer_index] &= ~row_1_offset;

      if (SSD1306_Buffer[pixel_2_buffer_index] & row_1_offset)
        SSD1306_TerminalBuffer[pixel_2_buffer_index] |= row_1_offset;
      else
        SSD1306_TerminalBuffer[pixel_2_buffer_index] &= ~row_1_offset;

      if (SSD1306_Buffer[pixel_3_buffer_index] & row_2_offset)
        SSD1306_TerminalBuffer[pixel_3_buffer_index] |= row_2_offset;
      else
        SSD1306_TerminalBuffer[pixel_3_buffer_index] &= ~row_2_offset;

      if (SSD1306_Buffer[pixel_4_buffer_index] & row_2_offset)
        SSD1306_TerminalBuffer[pixel_4_buffer_index] |= row_2_offset;
      else
        SSD1306_TerminalBuffer[pixel_4_buffer_index] &= ~row_2_offset;

      if (SSD1306_Buffer[pixel_5_buffer_index] & row_3_offset)
        SSD1306_TerminalBuffer[pixel_5_buffer_index] |= row_3_offset;
      else
        SSD1306_TerminalBuffer[pixel_5_buffer_index] &= ~row_3_offset;

      if (SSD1306_Buffer[pixel_6_buffer_index] & row_3_offset)
        SSD1306_TerminalBuffer[pixel_6_buffer_index] |= row_3_offset;
      else
        SSD1306_TerminalBuffer[pixel_6_buffer_index] &= ~row_3_offset;

      if (SSD1306_Buffer[pixel_7_buffer_index] & row_4_offset)
        SSD1306_TerminalBuffer[pixel_7_buffer_index] |= row_4_offset;
      else
        SSD1306_TerminalBuffer[pixel_7_buffer_index] &= ~row_4_offset;

      if (SSD1306_Buffer[pixel_8_buffer_index] & row_4_offset)
        SSD1306_TerminalBuffer[pixel_8_buffer_index] |= row_4_offset;
      else
        SSD1306_TerminalBuffer[pixel_8_buffer_index] &= ~row_4_offset;

      if (move_cursor) {
        // Move terminal cursor to the position of the pixel batch using escape codes
        printf("\033[%d;%dH", y / 4 + 2, x / 2 + 2);
        move_cursor = false;
      }

      // Calculate octant
      uint8_t octant_selector = 0x00;

      if (SSD1306_Buffer[pixel_1_buffer_index] & row_1_offset)
        octant_selector |= 1;
      if (SSD1306_Buffer[pixel_2_buffer_index] & row_1_offset)
        octant_selector |= 1 << 1;
      if (SSD1306_Buffer[pixel_3_buffer_index] & row_2_offset)
        octant_selector |= 1 << 2;
      if (SSD1306_Buffer[pixel_4_buffer_index] & row_2_offset)
        octant_selector |= 1 << 3;
      if (SSD1306_Buffer[pixel_5_buffer_index] & row_3_offset)
        octant_selector |= 1 << 4;
      if (SSD1306_Buffer[pixel_6_buffer_index] & row_3_offset)
        octant_selector |= 1 << 5;
      if (SSD1306_Buffer[pixel_7_buffer_index] & row_4_offset)
        octant_selector |= 1 << 6;
      if (SSD1306_Buffer[pixel_8_buffer_index] & row_4_offset)
        octant_selector |= 1 << 7;

      printf("%s", octant_table[octant_selector]);
    }

    if (draw_start)
      printf("║\n"); // Right border
  }

  if (draw_start) {
    // Bottom border
    printf("╚");
    for (x = 0; x < SSD1306_WIDTH / 2; x++)
      printf("═");
    printf("╝\n");

    // Initial drawing has ended. Now rely on line updates
    draw_start = false;
  }

  fflush(stdout);

  // Move terminal cursor below the screen
  printf("\033[%d;%dH", SSD1306_HEIGHT / 4 + 3, 1);
}
