#pragma once
#include <stdint.h>
#include <tiny_gui/config.h>
#include <tiny_gui/geometry.h>
#include <stdio.h>

namespace tiny_gui {

class FrameBuffer{
public:
    virtual void write (tiny_gui::color_type color, uint32_t x, uint32_t y) {}
    virtual void set_all (tiny_gui::color_type color) {}
    virtual void write_rect (tiny_gui::color_type color, const Rect& rect) {}
    virtual void write_hline (tiny_gui::color_type color, uint32_t x0, uint32_t x1, uint32_t y) {}
    virtual void write_vline (tiny_gui::color_type color, uint32_t x, uint32_t y0, uint32_t y1) {}
    virtual void write_start () {}
    virtual void write_end () {}
};

class FrameBufferMemory : public FrameBuffer{
private:
    tiny_gui::color_type* _data;
    uint32_t _width;
    uint32_t _height;
public:
    FrameBufferMemory (tiny_gui::color_type* _data, uint32_t width, uint32_t height) :
        _data(_data),
        _width(width),
        _height(height)
    {}


    void write (tiny_gui::color_type color, uint32_t x, uint32_t y) {
        _data[y * _width + x] = color;
    }

    void set_all (tiny_gui::color_type color) {
        tiny_gui_memset(_data, color, _width * _height);
    }

    void write_rect (tiny_gui::color_type color, const Rect& rect) {
        if (rect.width() == _width) {
            uint32_t idx = _width * rect.top + rect.left;
            tiny_gui_memset(_data + idx, color, (rect.width() * rect.height()));
        }
        for (size_t i = 0; i < rect.height(); i++){
            write_hline(color, rect.left, rect.right, rect.top + i);
        }
    }

    void write_vline (tiny_gui::color_type color, uint32_t x, uint32_t y0, uint32_t y1) {
        for (int j = 0; j < y1 - y0; j++){
            uint32_t idx = (_width * (j + y0)) + x;
            _data[idx] = color;
        }
    }

    void write_hline (tiny_gui::color_type color, uint32_t x0, uint32_t x1, uint32_t y) {
        uint32_t idx = (_width * y) + x0;
        tiny_gui_memset(_data + idx, color, x1 - x0);
    }

    void write_start () {
    };

    void write_end () {
    };
};


} // end namespace