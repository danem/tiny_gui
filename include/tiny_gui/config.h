#pragma once
#include <stdint.h>

#ifndef TINY_GUI_COLOR_DEPTH_16
#define TINY_GUI_COLOR_DEPTH_32 
#endif

// #define TINY_GUI_USE_STRINGS


namespace tiny_gui {
#ifdef TINY_GUI_COLOR_DEPTH_32
using color_type = uint32_t;
#else
using color_type = uint16_t;
#endif
} // end namespace


