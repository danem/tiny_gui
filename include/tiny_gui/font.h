#pragma once

#include <stdint.h>

// Based on AdafruitGFX font format
namespace tiny_gui {

struct Glyph {
  uint32_t char_code;
  uint16_t bitmapOffset; ///< Pointer into GFXfont->bitmap
  uint8_t width;         ///< Bitmap dimensions in pixels
  uint8_t height;        ///< Bitmap dimensions in pixels
  uint8_t xAdvance;      ///< Distance to advance cursor (x axis)
  int8_t xOffset;        ///< X dist from cursor pos to UL corner
  int8_t yOffset;        ///< Y dist from cursor pos to UL corner
};


/// Data stored for FONT AS A WHOLE
struct Font {
  const uint8_t *bitmap;  ///< Glyph bitmaps, concatenated
  const Glyph *glyph;  ///< Glyph array
  uint16_t first;   ///< ASCII extents (first char)
  uint16_t last;    ///< ASCII extents (last char)
  uint8_t yAdvance; ///< Newline distance (y axis)
  uint32_t count;
};

bool getGlyph (const Font& font, char symbol, Glyph& res);

} // end namespace