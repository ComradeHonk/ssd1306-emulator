#include "experimental.h"
#include "ssd1306.h"
#include "ssd1306_conf.h"
#include "stdint.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifdef EXP_OCTANT_RENDERER
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
  uint16_t x, y, i, j;

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
      size_t pixel_buffer_indices[4][2];
      uint8_t pixel_offsets[4];

      for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++)
          pixel_buffer_indices[i][j] = (x + j) + ((y + i) / 8) * SSD1306_WIDTH;
        pixel_offsets[i] = 1 << ((y + i) % 8);
      }

      // If all pixels haven't changed, do not re-render them
      bool pixel_changed = false;

      for (i = 0; !pixel_changed && i < 4; i++)
        for (j = 0; !pixel_changed && j < 2; j++)
          if ((SSD1306_Buffer[pixel_buffer_indices[i][j]] ^
               SSD1306_TerminalBuffer[pixel_buffer_indices[i][j]]) &
              pixel_offsets[i])
            pixel_changed = true;

      if (!draw_start && !pixel_changed) {
        move_cursor = true;
        continue;
      }

      // Synchronize buffers
      for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
          if (SSD1306_Buffer[pixel_buffer_indices[i][j]] & pixel_offsets[i])
            SSD1306_TerminalBuffer[pixel_buffer_indices[i][j]] |= pixel_offsets[i];
          else
            SSD1306_TerminalBuffer[pixel_buffer_indices[i][j]] &= ~pixel_offsets[i];
        }
      }

      if (move_cursor) {
        // Move terminal cursor to the position of the pixel batch using escape codes
        printf("\033[%d;%dH", y / 4 + 2, x / 2 + 2);
        move_cursor = false;
      }

      // Calculate octant
      uint8_t octant_selector = 0x00;

      for (i = 0; i < 4; i++)
        for (j = 0; j < 2; j++)
          if (SSD1306_Buffer[pixel_buffer_indices[i][j]] & pixel_offsets[i])
            octant_selector |= 1 << (2 * i + j);

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
#endif
