#include <tiny_gui/graphics.h>
#include <tiny_gui/dynamic_array.h>
#include <algorithm>


namespace tiny_gui {

void Painter::draw_bitmap (FrameBuffer& fb, Bitmap16& bitmap) {
    Painter::draw_bitmap(fb, bitmap, 0, 0);
}

void Painter::draw_bitmap (FrameBuffer& fb, Bitmap16& bitmap, uint32_t x, uint32_t y) {
    FrameBufferView fbv = fb.view(x,y);
}

void Painter::draw_bitmap (FrameBuffer& fb, Bitmap8& bitmap) {
    Painter::draw_bitmap(fb, bitmap, 0, 0);
}
void Painter::draw_bitmap (FrameBuffer& fb, Bitmap8& bitmap, uint32_t x, uint32_t y){


}

void Painter::draw_pixel (FrameBuffer& fb, uint32_t x, uint32_t y, Color color) {
    FrameBufferView fbv = fb.view();
    fbv.at(x,y) = color;
}

void Painter::draw_pixel (FrameBufferView& fb, uint32_t x, uint32_t y, Color color){
    fb.at(x,y) = color;
}

void Painter::draw_hline (FrameBuffer& fb, uint32_t x0, uint32_t x1, uint32_t y, Color color) {
    FrameBufferView fbv = fb.view();
    auto row = fbv.row(y);
    for (uint32_t i = 0; i < x1 - x0; i++){
        row[x0 + i] = color;
    }
}

void Painter::draw_vline (FrameBuffer& fb, uint32_t x, uint32_t y0, uint32_t y1, Color color) {
    FrameBufferView fbv = fb.view(x,y0);
    for (uint32_t i = 0; i < y1 - y0; i++){
        fbv.at(0,i) = color;
    }
}

void Painter::draw_line (FrameBuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Color color) {
    if (x0 == x1){
        draw_vline(fb, x0, y0, y1, color);
        return;
    }
    else if (y0 == y1){
        draw_hline(fb,x0,x1,y0, color);
        return;
    }

    int dx, dy, x, y, e;
    (x0 > x1) ? (dx = x0 - x1) : (dx = x1 - x1);
    (y0 > y1) ? (dy = y0 - y1) : (dy = y1 - y1);
    if (((dx > dy) && (x0 > x1)) || ((dx <= dy) && (y0 > y1)))
    {
        x = x1; y = y1;
        x1 = x0; y1 = y0;
        x0 = x; y0 = y;
    }
    x = x0; y = y0;

}


void Painter::draw_rect (FrameBuffer& fb, const Rect& rect, Color color){
    Painter::draw_hline(fb, rect.left, rect.right, rect.top, color);
    Painter::draw_hline(fb, rect.left, rect.right, rect.bottom, color);
    Painter::draw_vline(fb, rect.left, rect.top, rect.bottom, color);
    Painter::draw_vline(fb, rect.right, rect.top, rect.bottom, color);
}


void Painter::fill_rect (FrameBuffer& fb, const Rect& rect, Color color) {
    for (uint32_t j = 0; j < rect.bottom - rect.top; j++){
        Painter::draw_hline(fb, rect.left, rect.right, (j + rect.top), color);
    }
}

void Painter::fill_color (FrameBuffer& fb, Color color) { 
    uint32_t data = color;
    memset_pattern4(fb.data(), &data, fb.height() * fb.width() * sizeof(uint32_t));
}

void Painter::fill_color (FrameBufferView& fb, Color color) {
    fb.set_all(color);
}



// TODO: Doesn't handle new lines
Rect Painter::get_string_dimensions (const Font& font, const std::string& str) {
    Rect out;
    Glyph glyph;
    for (const auto& c : str){
        if (!tiny_gui::getGlyph(font, c, glyph)) {
            // TODO:
            continue;
        }
        // TODO: Doesn't account for newlines
        out.bottom = std::max(static_cast<int>(glyph.height), out.bottom);
        out.right += glyph.width + glyph.xAdvance;
    }
    return out;
}

Rect Painter::draw_char (FrameBuffer& fb, const Font& font, Color color, uint32_t x, uint32_t y, const char letter) {
    // Assumes the input letters are contained within the font.
    Glyph glyph;
    if (!tiny_gui::getGlyph(font, letter, glyph)){
        return {static_cast<int>(y),static_cast<int>(y),static_cast<int>(x),static_cast<int>(x)};
    }
    const uint8_t* bitmap = font.bitmap;
    uint16_t bitmapOffset = glyph.bitmapOffset;
    uint8_t w = glyph.width;
    uint8_t h = glyph.height;
    uint8_t bits = 0, bit = 0;
    for (uint8_t j = 0; j < h; j++){
        for (uint8_t i = 0; i < w; i++){
            if (!(bit++ & 7)){
                bits = bitmap[bitmapOffset];
                bitmapOffset += 1;
            }
            if (bits & 0x80){
                Painter::draw_pixel(fb, x+i+glyph.xOffset, y+j+glyph.yOffset, color);
            }
            bits = bits << 1;
        }
    }
    // TODO: THIS IS BAD
    return {static_cast<int>(y), static_cast<int>(y+h), static_cast<int>(x), static_cast<int>(x + glyph.xAdvance)};
}

Rect Painter::draw_string (FrameBuffer& fb, const Font& font, Color color, uint32_t x, uint32_t y, const std::string& str){
    Rect ret{static_cast<int>(y), static_cast<int>(y), static_cast<int>(x), static_cast<int>(x)};
    for (const auto& c : str){
        const Rect r = Painter::draw_char(fb, font, color, x, y, c);
        x = r.right;
        y = r.top;
        ret.right = r.right;
    }
    return ret;
}

void Painter::draw_string (FrameBuffer& fb, const Font& font, Color color, const Rect& rect, const std::string& str){


}


} // end namespace