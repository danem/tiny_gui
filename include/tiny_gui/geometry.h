#pragma once

namespace tiny_gui {

// TODO: Fix signed/unsigned type issue
struct Rect {
    int top = 0;
    int bottom = 0;
    int left = 0;
    int right = 0;

    Rect () {}

    Rect (int top, int bottom, int left, int right) :
        top(top), bottom(bottom),
        left(left), right(right)
    {}

    inline int width () const { return right - left; }
    inline int height () const { return bottom - top; }

    inline bool point_inside (int x, int y){
		return x >= left && x <= right && y >= top && y <= bottom;
    }

    inline void position (int x, int y) {
        int h = height();
        int w = width();
        top = y; bottom = top + h;
        left = x; right = left + w;
    }
};

struct Point {
    int x = 0;
    int y = 0;
    Point (){}
    Point (int x, int y) : x(x), y(y) {}

};

} // end namespace