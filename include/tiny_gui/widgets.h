#pragma once
#include <tiny_gui/geometry.h>
#include <tiny_gui/font.h>
#include <tiny_gui/color.h>
#include <tiny_gui/display.h>
#include <string>

namespace tiny_gui {

struct Style {
    const Font* font;
    Color font_color = {0};
    Color background_color = {0};
    Color active_color = {0};
    Color disabled_color = {0};
    Color hover_color = {0};
};

class StyleBuilder {
private:
    Style _style;
public:
    StyleBuilder(){}
    StyleBuilder(const Style& style) : _style(style) {}

    StyleBuilder& set_font (const Font* font, Color color = {0}) {
        _style.font = font;
        _style.font_color = color;
        return *this;
    }

    StyleBuilder& button_color (Color background, Color active, Color disabled, Color hover) {
        _style.background_color = background;
        _style.disabled_color = disabled;
        _style.active_color = active;
        _style.hover_color = hover;
        return *this;
    }

    StyleBuilder& background_color (Color background) {
        _style.background_color = background;
        return *this;
    }

    Style build () {
        return _style;
    }
};


enum class WidgetState {
    DEFAULT,
    ACTIVE,
    INACTIVE,
    SELECTED,
    DISABLED
};

enum class MouseEventState {
    MOUSE_DOWN, MOUSE_UP, MOUSE_OVER, NONE
};

class Widget {
protected:
    MouseEventState _mouseState;
    WidgetState _widgetState;

public:
    virtual void render (FrameBuffer& fb, const Rect& rect) = 0;
    void setWidgetState (WidgetState state) { _widgetState = state; }
    void setMouseEventState (MouseEventState state) { _mouseState = state; }
};

class Container : public Widget {
private:
    Color _color;
public:
    Container (Color color) :
        _color(color)
    {}

    void render (FrameBuffer& fb, const Rect& rect);

};

class Label : public Widget {
private:
    std::string _text;
    Style _style;
public:
    Label(Style style, const std::string& str) :
        _style(style),
        _text(str)
    {}

    void setText (const std::string& str);
    void render (FrameBuffer& fb, const Rect& rect);
};

class PushButton : public Widget {
public:
    using button_push_handler = void (const char* id);

private:
    Style _style;
    std::string _text;
    button_push_handler* _click_handler;

public:
    PushButton (Style style, std::string text) :
        _style(style),
        _text(text)
    {}


    void setText (const std::string& text);
    void render (FrameBuffer& fb, const Rect& rect);

};


} // end namespace