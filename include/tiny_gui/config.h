#pragma once
#include <stdint.h>

// Set TINY_GUI_COLOR_ABGR to automatically convert colors to
// ABGR format. 
#ifndef TINY_GUI_COLOR_ABGR
// Default is ARGB
#define TINY_GUI_COLOR_ARGB
#endif

// Set TINY_GUI_COLOR_DEPTH_16 to work with 16 bit color
#ifndef TINY_GUI_COLOR_DEPTH_16
// Default is 32bit
#define TINY_GUI_COLOR_DEPTH_32 
#endif

// Set TINY_GUI_NO_CPP_STRINGS to remove c++ string support
// #define TINY_GUI_NO_CPP_STRINGS
// #define TINY_GUI_USE_CPP_STRINGS
// #endif


namespace tiny_gui {
#ifdef TINY_GUI_COLOR_DEPTH_32
using color_type = uint32_t;
#else
using color_type = uint16_t;
#endif
} // end namespace


