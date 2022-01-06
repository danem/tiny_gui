#pragma once

#include <tiny_gui/config.h>
#include <tiny_gui/bitmap.h>
#include <tiny_gui/color.h>
#include <tiny_gui/display.h>
#include <tiny_gui/layout.h>
#include <tiny_gui/font.h>
#include <tiny_gui/widgets.h>
#include <string>

namespace tiny_gui {

class Painter {
private:
public:
    static void draw_pixel (FrameBuffer& fb, uint32_t x, uint32_t y, Color color);
    static void draw_pixel (FrameBufferView& fb, uint32_t x, uint32_t y, Color color);

    static void draw_line (FrameBuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Color color);
    static void draw_hline (FrameBuffer& fb, uint32_t x0, uint32_t x1, uint32_t y, Color color);
    static void draw_vline (FrameBuffer& fb, uint32_t x, uint32_t y0, uint32_t y1, Color color);
    static void draw_rect (FrameBuffer& fb, const Rect& rect, Color color);
    static void fill_rect (FrameBuffer& fb, const Rect& rect, Color color);

    static void draw_bitmap (FrameBuffer& fb, Bitmap16& bitmap);
    static void draw_bitmap (FrameBuffer& fb, Bitmap16& bitmap, uint32_t x, uint32_t y);

    static void draw_bitmap (FrameBuffer& fb, Bitmap8& bitmap);
    static void draw_bitmap (FrameBuffer& fb, Bitmap8& bitmap, uint32_t x, uint32_t y);

    static void fill_color (FrameBuffer& fb, Color color);     
    static void fill_color (FrameBufferView& fb, Color color);     

    static Rect get_string_dimensions (const Font& font, const std::string& str);
    static void draw_string (FrameBuffer& fb, const Font& font, Color color, const Rect& rect, const std::string& str);
    static Rect draw_string (FrameBuffer& fb, const Font& font, Color color, uint32_t x, uint32_t y, const std::string& str);
    static Rect draw_char (FrameBuffer& fb, const Font& font, Color color, uint32_t x, uint32_t y, const char letter);
};

} // end namespace