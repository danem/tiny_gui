#pragma once
#include <stdint.h>
#include <tiny_gui/config.h>
#include <tiny_gui/geometry.h>

namespace tiny_gui {


// TODO: Investigate having this interface writing directly to 
// a display if so desired.
class FrameBufferView {
public:
    using value_type = tiny_gui::color_type;
private:
    tiny_gui::color_type* _data;
    uint32_t _x;
    uint32_t _y;
    uint32_t _width;
    uint32_t _height;

public:
    FrameBufferView (tiny_gui::color_type* data, uint32_t width, uint32_t height, uint32_t x = 0, uint32_t y = 0) :
        _data(data),
        _width(width), _height(height),
        _x(x), _y(y)
    {}

    tiny_gui::color_type* row (int y) { 
        int idx = (y+_y) * _width + _x;
        return _data + idx;
    }

    tiny_gui::color_type& at (int x, int y) {
        return row(y)[x];
    }

    tiny_gui::color_type& idx (uint32_t idx){
        return _data[idx];
    }

    void set_all (tiny_gui::color_type value) {
        for (uint32_t j = 0; j < _height; j++){
            tiny_gui::color_type* r = row(j);
            for (uint32_t i = 0; i < _width; i++){
                r[i] = value;
            }
        }
    }
};

class FrameBufferBase {
protected:
    tiny_gui::color_type* _data;
    uint32_t _width;
    uint32_t _height;

public:
    uint32_t width () { return _width; }
    uint32_t height () { return _height; }
    tiny_gui::color_type* data() { return _data; }
};


class FrameBuffer : public FrameBufferBase {
public:
    FrameBuffer (tiny_gui::color_type* data, uint32_t width, uint32_t height) {
        _data = data;
        _width = width;
        _height = height;
    }

    void* data () { return _data; }

    FrameBufferView view () {
        return {_data, _width, _height};
    }

    FrameBufferView view (uint32_t x, uint32_t y) {
        return {_data, _width, _height, x, y};
    }

    FrameBufferView view (const Rect& rect){
        // TODO: Fix this cast issue
        return {_data, 
            static_cast<uint32_t>(rect.width()),
            static_cast<uint32_t>(rect.height()),
            static_cast<uint32_t>(rect.left), 
            static_cast<uint32_t>(rect.top)
        };
    }
};

} // end namespace