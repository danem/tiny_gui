#pragma once
#include <stdint.h>
#include <tiny_gui/geometry.h>
#include <tiny_gui/display.h>
#include <tiny_gui/widgets.h>
#include <tiny_gui/linked_list.h>

namespace tiny_gui {

enum class Alignment {
    NONE,
    CENTER,
};

enum class SizePolicy {
    NONE,
    STRETCH
};

class Measurement {
protected:
    bool _deferred = false;
    float _percentage = 0;
    int _pixels = 0;

    Measurement (float value) {
        _percentage = value;
        _deferred = true;
    }

    Measurement (int pixels){
        _pixels = pixels;
    }

public:

    static Measurement Relative (float value) {
        return {value};
    }

    static Measurement Absolute (int pixels){
        return {pixels};
    }

    static Measurement A (int pixels){
        return {pixels};
    }

    static Measurement R (float value){
        return {value};
    }

    int value (int container){
        if (_deferred) return static_cast<int>(container * _percentage);
        return _pixels;
    }
};

struct LayoutProperties {
    Measurement width = Measurement::Absolute(0);
    Measurement height = Measurement::Absolute(0);
    Measurement pad_left = Measurement::Absolute(0);
    Measurement pad_right = Measurement::Absolute(0);
    Measurement pad_top = Measurement::Absolute(0);
    Measurement pad_bottom = Measurement::Absolute(0);
    Alignment vertical_alignment = Alignment::NONE;
    Alignment horizontal_alignment = Alignment::NONE;
    int spacing = 0;
    int left = 0;
    int top = 0;
};

class LayoutBuilder {
private:
    LayoutProperties _properties;
public:
    LayoutBuilder& dimensions (const Measurement& width, const Measurement& height) {
        _properties.width = width;
        _properties.height = height;
        return *this;
    }
    LayoutBuilder& dimensions_relative (float width, float height) {
        _properties.width = Measurement::Relative(width);
        _properties.height = Measurement::Relative(height);
        return *this;
    }

    LayoutBuilder& dimensions_absolute (int width, int height) {
        _properties.width = Measurement::Absolute(width);
        _properties.height = Measurement::Absolute(height);
        return *this;
    }

    LayoutBuilder& vertical_alignment (Alignment v){
        _properties.vertical_alignment = v;
        return *this;
    }
    
    LayoutBuilder& horizontal_alignment (Alignment v){
        _properties.horizontal_alignment = v;
        return *this;
    }

    LayoutBuilder& alignment (Alignment v, Alignment h) {
        _properties.horizontal_alignment = h;
        _properties.vertical_alignment = v;
        return *this;
    }

    LayoutBuilder& padding (const Measurement& top, const Measurement& bottom, const Measurement& left, const Measurement& right) {
        _properties.pad_top = top;
        _properties.pad_left = left;
        _properties.pad_bottom = bottom;
        _properties.pad_right = right;
        return *this;
    }

    LayoutBuilder& position (int left, int top){
        _properties.left = left;
        _properties.top = top;
        return *this;
    }

    LayoutBuilder& spacing (int spacing){
        _properties.spacing = spacing;
        return *this;
    }

    LayoutProperties build () {
        return _properties;
    }

    operator LayoutProperties() {
        return _properties;
    }
};


class LayoutItem;

using LayoutCalculator = Rect (const Rect& container, const LayoutProperties& layout, LayoutItem* children);

Rect DefaultLayout (const Rect& container, const LayoutProperties& layout, LayoutItem* children);
Rect VerticalLayout (const Rect& container, const LayoutProperties& layout, LayoutItem* children);
Rect HorizontalLayout (const Rect& container, const LayoutProperties& layout, LayoutItem* children);



class LayoutItem {
public:
    // TODO: Figure out how to make this private

    // Intrusive linked list. This allows us to create
    // dynamic lists without any memory allocatioh.
    // However, this will NOT work with any subclasses of LayoutItem.
    list_head _sibling_list;
    LayoutItem* _children;
    LayoutCalculator* _layoutFn;
    Rect _computedDims;
    LayoutProperties _layout;
    Widget* _widget;

private:
protected:

    // TODO: Look at smart pointers

public:
    LayoutItem () {}

    LayoutItem (LayoutProperties layout, LayoutCalculator* layoutFn = DefaultLayout) :
        _layout(layout),
        _layoutFn(layoutFn)
    {}

    LayoutItem (Widget& widget, LayoutProperties layout, LayoutCalculator* layoutFn = DefaultLayout) :
        _widget(&widget),
        _layout(layout),
        _layoutFn(layoutFn)
    {}

    LayoutItem (Widget* widget, LayoutProperties layout, LayoutCalculator* layoutFn = DefaultLayout) :
        _widget(widget),
        _layout(layout),
        _layoutFn(layoutFn)
    {}

    Rect calculateLayout (uint32_t width, uint32_t height, const Point& offset = {0,0});
    Rect calculateLayout (const Rect& container, const Point& offset = {0,0});
    void render (FrameBuffer& fb);
    void addChild (LayoutItem& item);
    void setWidget (Widget& widget);
};








} // end namespace  