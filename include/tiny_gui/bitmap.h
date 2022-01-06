#pragma once

#include <tiny_gui/dynamic_array.h>
#include <stdint.h>

namespace tiny_gui {

struct BitmapBase {
    uint32_t width;
    uint32_t height;
};

// TODO: Maybe support 32 bit
template <class T>
struct Bitmap : BitmapBase {
    dynamic_array<T> data;
};

using Bitmap16 = Bitmap<uint16_t>;
using Bitmap8 = Bitmap<uint8_t>;

} // end namespace