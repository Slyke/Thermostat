// Images can be converted to XBM format by using the online converter here:
// https://www.online-utility.org/image/convert/to/XBM

// The output must be pasted in a header file, renamed and adjusted to appear
// as as a const unsigned char array in PROGMEM (FLASH program memory).

// The xbm format adds padding to pixel rows so they are a whole number of bytes
// In this example 50 pixel width means 56 bits = 7 bytes
// the 50 height then means array uses 50 x 7 = 350 bytes of FLASH
// The library ignores the padding bits when drawing the image on the display.

// Example of the correct format is shown below

#include <pgmspace.h>

#define icon_X_width 32
#define icon_X_height 32
#define icon_X_color 255, 0, 0
PROGMEM const unsigned char icon_X[] = {
  0x07, 0x00, 0x00, 0x38, 0x0F, 0x00, 0x00, 0x3C, 0x1F, 0x00, 0x00, 0x3E, 
  0x3E, 0x00, 0x00, 0x1F, 0x7C, 0x00, 0x80, 0x0F, 0xF8, 0x00, 0xC0, 0x07, 
  0xF0, 0x01, 0xE0, 0x03, 0xE0, 0x03, 0xF0, 0x01, 0xC0, 0x07, 0xF8, 0x00, 
  0x80, 0x0F, 0x7C, 0x00, 0x00, 0x1F, 0x3E, 0x00, 0x00, 0x3E, 0x1F, 0x00, 
  0x00, 0xFC, 0x0F, 0x00, 0x00, 0xF8, 0x07, 0x00, 0x00, 0xF0, 0x03, 0x00, 
  0x00, 0xF0, 0x03, 0x00, 0x00, 0xF8, 0x07, 0x00, 0x00, 0xFC, 0x0F, 0x00, 
  0x00, 0x3E, 0x1F, 0x00, 0x00, 0x1F, 0x3E, 0x00, 0x80, 0x0F, 0x7C, 0x00, 
  0xC0, 0x07, 0xF8, 0x00, 0xE0, 0x03, 0xF0, 0x01, 0xF0, 0x01, 0xE0, 0x03, 
  0xF8, 0x00, 0xC0, 0x07, 0x7C, 0x00, 0x80, 0x0F, 0x3E, 0x00, 0x00, 0x1F, 
  0x1F, 0x00, 0x00, 0x3E, 0x0F, 0x00, 0x00, 0x3C, 0x07, 0x00, 0x00, 0x38, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };