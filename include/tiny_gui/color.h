#pragma once
#include <stdint.h>
#include <tiny_gui/config.h>

namespace tiny_gui {


namespace utility {

inline uint32_t create_rgb (uint32_t r, uint32_t g, uint32_t b){
    return (0xFF << 24) | (r << 16) | (g << 8) | b;
}

inline uint32_t create_argb (uint32_t a, uint32_t r, uint32_t g, uint32_t b){
    return (a << 24) | (r << 16) | (g << 8) | b;
}

inline uint16_t color32to16 (uint32_t color) {
    return ((color & 0xFF) >> 3) | ((color & 0xFC00) >> 5) | ((color & 0xF8000) >> 8);
}

inline uint32_t color16to32 (uint16_t color){
    return (0xFF << 24) | ((color & 0x1F) << 3) | ((color & 0x7E0) << 5) | ((color & 0xF800) << 8);
}

inline tiny_gui::color_type convert_color (uint32_t color) {
#ifdef TINY_GUI_COLOR_DEPTH_32
    return color;
#else
    return color32to16(color);
#endif
}

inline tiny_gui::color_type convert_color (uint16_t color) {
#ifdef TINY_GUI_COLOR_DEPTH_32
    return color16to32(color);
#else
    return color;
#endif
}

} // end namespace

struct Color
{
    tiny_gui::color_type _data;

    Color (uint32_t color){
        _data = tiny_gui::utility::convert_color(color);
    }

    operator color_type(){
        return _data;
    }
};

static const Color WHITE {0xFFFFFFFF};
static const Color BLACK {0};
static const Color RED {0xFF0000FF};
static const Color BLUE {0x00FF00FF};
static const Color GREEN {0x0000FFFF};

} // end namespace