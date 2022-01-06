#include <tiny_gui/font.h>

namespace tiny_gui {

namespace {
    // Binary search to find glyph
    bool find_glyph (const Glyph* glyphs, uint32_t size, char symbol, Glyph& res){
        uint32_t start_idx = 0;
        uint32_t end_idx = size;
        while (start_idx <= end_idx){
            uint32_t half = (start_idx + end_idx) / 2;
            if (glyphs[half].char_code == symbol){
                res = glyphs[half];
                return true;
            }
            else if (glyphs[half].char_code < symbol) {
                start_idx = half + 1;
            }
            else {
                end_idx = half - 1;
            }
        }
        return false;
    }
}

bool getGlyph (const Font& font, char symbol, Glyph& res) {
    return find_glyph(font.glyph, font.count, symbol, res);
}

} // end namespace