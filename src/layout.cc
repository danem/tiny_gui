#include <tiny_gui/layout.h>

namespace tiny_gui {

template <class T>
T clamp (T low, T high, T value) {
    if (value < low) return low;
    else if (value > high) return high;
    return value;
}

Rect clampRect (const Rect& fixed, const Rect& other){
    Rect ret = other;
    ret.top = clamp(fixed.top, fixed.bottom, ret.top);
    ret.bottom = clamp(fixed.top, fixed.bottom, ret.bottom);
    ret.left = clamp(fixed.left, fixed.right, ret.left);
    ret.right = clamp(fixed.left, fixed.right, ret.right);
    return ret;
}

Rect DefaultLayout (const Rect& container, const LayoutProperties& layout, LayoutItem* children) {
    if (children) {
        for(list_head& list : list_iterator{children->_sibling_list}){
            LayoutItem* item = list_entry(&list, LayoutItem, _sibling_list);
            item->calculateLayout(container);
        }
    }
}

Rect VerticalLayout (const Rect& container, const LayoutProperties& layout, LayoutItem* children) {
    int top = 0;
    if (children) {
        for(list_head& list : list_iterator{children->_sibling_list}){
            LayoutItem* item = list_entry(&list, LayoutItem, _sibling_list);
            Rect resRect = item->calculateLayout(container, {0, top});
            top = resRect.bottom + layout.spacing;
        }
    }
}

Rect HorizontalLayout (const Rect& container, const LayoutProperties& layout, LayoutItem* children) {
    int right = 0;
    if (children) {
        for(list_head& list : list_iterator{children->_sibling_list}){
            LayoutItem* item = list_entry(&list, LayoutItem, _sibling_list);
            Rect resRect = item->calculateLayout(container, {right, 0});
            right = resRect.right + layout.spacing;
        }
    }
}


Rect LayoutItem::calculateLayout (const Rect& container, const Point& offset) {
    int width = _layout.width.value(container.width());
    int height = _layout.height.value(container.height());
    int cx = container.left + (container.width()/2);
    _computedDims.left = _layout.left + offset.x;
    _computedDims.top = _layout.top + offset.y;

    if (_layout.vertical_alignment == Alignment::CENTER){
        int cy = container.top + (container.height()/2);
        _computedDims.top += cy - (height / 2);
    }
    else _computedDims.top += container.top;
    if (_layout.horizontal_alignment == Alignment::CENTER){
        int cx = container.left + (container.width()/2);
        _computedDims.left += cx - width / 2;
    }
    else _computedDims.left += container.left;

    _computedDims.right = _computedDims.left + width;
    _computedDims.bottom = _computedDims.top + height;
    _computedDims = clampRect(container, _computedDims);

    if (_layoutFn) {
        _layoutFn(_computedDims, _layout, _children);
    }
    return _computedDims;
}

Rect LayoutItem::calculateLayout (uint32_t width, uint32_t height, const Point& offset){
    Rect r{0, static_cast<int>(height), 0, static_cast<int>(width)};
    return calculateLayout(r, offset);
}

void LayoutItem::render (FrameBuffer& fb) {
    if (_widget) _widget->render(fb, _computedDims);
    if (_children) {
        for(list_head& list : list_iterator{_children->_sibling_list}){
            LayoutItem* item = list_entry(&list, LayoutItem, _sibling_list);
            item->render(fb);
        }
    }
}

void LayoutItem::addChild (LayoutItem& item) {
    if (!_children) {
        _children = &item;
    }
    else {
        list_append(_children->_sibling_list, item._sibling_list);
    }
}

void LayoutItem::setWidget (Widget& widget) {
    _widget = &widget;
}

} // end namespace