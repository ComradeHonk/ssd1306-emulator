// Private configuration file for the SSD1306 library.

#ifndef __SSD1306_CONF_H__
#define __SSD1306_CONF_H__

// Include all fonts by default
#define SSD1306_INCLUDE_FONT_6x8
#define SSD1306_INCLUDE_FONT_7x10
#define SSD1306_INCLUDE_FONT_11x18
#define SSD1306_INCLUDE_FONT_16x26

#define SSD1306_INCLUDE_FONT_16x24

#define SSD1306_INCLUDE_FONT_16x15

// The width of the screen can be set using this
// define. The default value is 128
#define SSD1306_WIDTH 128

// The height can be changed as well if necessary,
// but it must be an even number or else the last row won't be rendered.
// The default value is 64
#define SSD1306_HEIGHT 64

// Flags for enabling experimental features.
// Experimental features are not guaranteed to work

// Uses octants for rendering instead of half blocks. This greatly improves performance
// at the cost of compatibility, as not every terminal font supports them.
// Octant renderer requires height to be divisible by 4 and width must be an even number.
// This is a technical limitation as one octant represents 2x4 area of pixels
// #define EXP_OCTANT_RENDERER

#endif /* __SSD1306_CONF_H__ */
