#include <tiny_gui/widgets.h>
#include <tiny_gui/graphics.h>


namespace tiny_gui {

static Rect centered_rect (const Rect& fixed, const Rect& other){
    Rect out = other;
    int cx = fixed.left + (fixed.width() / 2);
    int cy = fixed.top + (fixed.height() / 2);

    out.left = cx - (other.width() / 2);
    out.top = cy - (other.height() / 2);
    return out;
}

void Container::render (FrameBuffer& fb, const Rect& rect){
    Painter::fill_rect(fb, rect, _color);
}

void PushButton::render (FrameBuffer& fb, const Rect& rect) {
    Color buttonColor{0};
    if (_widgetState == WidgetState::ACTIVE) buttonColor = _style.active_color;
    else if (_widgetState == WidgetState::DISABLED) buttonColor = _style.disabled_color;
    else if (_mouseState == MouseEventState::MOUSE_OVER) buttonColor = _style.hover_color;
    else buttonColor = _style.background_color;
    Painter::fill_rect(fb, rect, buttonColor);

    Rect str_rect = Painter::get_text_bounds(*_style.font,0,0, _text);
    Rect new_rect = centered_rect(rect, str_rect);
    Painter::draw_string(fb, *_style.font, _style.font_color, new_rect.left, new_rect.top, _text);
}

void Label::setText (const std::string& str){
    _text = str;
}

void Label::render (FrameBuffer& fb, const Rect& rect){
    Painter::draw_string(fb, *_style.font, _style.font_color, rect.left, rect.top, _text);
}


} // end namespace