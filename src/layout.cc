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

// TODO: Make LayoutItem* const
void __calculateStretch (const Rect& container, const LayoutProperties& layout, LayoutItem* children, LayoutState& ls){
    int childrenCount = 0;
    if (children) childrenCount = list_length(children->_sibling_list);

    int availableWidth = container.width() - layout.pad_left - layout.pad_right - (layout.spacing * (childrenCount-1));
    int availableHeight = container.height() - layout.pad_top - layout.pad_bottom - (layout.spacing * (childrenCount-1));
    int stretchXItems = 0;
    int stretchYItems = 0;

    if (children) {
        for(list_head& list : list_iterator{children->_sibling_list}){
            LayoutItem* item = list_entry(&list, LayoutItem, _sibling_list);
            if (item->_layout.width_policy == SizePolicy::STRETCH) stretchXItems += 1;
            else availableWidth -= item->_layout.width.value(container.width());

            if (item->_layout.height_policy == SizePolicy::STRETCH) stretchYItems += 1;
            else availableHeight -= item->_layout.height.value(container.height());
        }
        ls.stretchSizeX = (int)((float)availableWidth / (float)stretchXItems);
        ls.stretchSizeY = (int)((float)availableHeight / (float)stretchYItems);
    }
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
    LayoutState state;
    Rect padded = container;
    padded.left += layout.pad_left;
    padded.top  += layout.pad_top;
    padded.right -= layout.pad_right;
    padded.bottom -= layout.pad_bottom;
    if (children) {
        __calculateStretch(padded, layout, children, state);
        for(list_head& list : list_iterator{children->_sibling_list}){
            LayoutItem* item = list_entry(&list, LayoutItem, _sibling_list);
            Rect resRect = item->_calculateLayoutSelf(state, padded);
            item->_calculateLayoutChildren(state, padded);
            state.offsetY = resRect.bottom + layout.spacing;
        }
    }
}

Rect HorizontalLayout (const Rect& container, const LayoutProperties& layout, LayoutItem* children) {
    LayoutState state;
    Rect padded = container;
    padded.left += layout.pad_left;
    padded.top  += layout.pad_top;
    padded.right -= layout.pad_right;
    padded.bottom -= layout.pad_bottom;
    if (children) {
        __calculateStretch(padded, layout, children, state);
        for(list_head& list : list_iterator{children->_sibling_list}){
            LayoutItem* item = list_entry(&list, LayoutItem, _sibling_list);
            Rect resRect = item->_calculateLayoutSelf(state, padded);
            item->_calculateLayoutChildren(state, padded);
            state.offsetX = resRect.right + layout.spacing;
        }
    }
}

Rect LayoutItem::_calculateLayoutSelf (LayoutState& state, const Rect& container) {
    // Calculate position and size of LayoutItem, but not its children.
    // Handle centering, and stretching here
    int width = 0;
    int height = 0;

    if (_layout.width_policy == SizePolicy::STRETCH) width = state.stretchSizeX;
    else width = _layout.width.value(container.width());

    if (_layout.height_policy == SizePolicy::STRETCH) height = state.stretchSizeY;
    else height = _layout.height.value(container.height());

    int cx = container.left + (container.width() / 2);
    int cy = container.top + (container.height() / 2);
    int x = _layout.left + state.offsetX;
    int y = _layout.top + state.offsetY;

    if (_layout.vertical_alignment == Alignment::CENTER) {
        y = cy - (height / 2);
    }
    else y += container.top;

    if (_layout.horizontal_alignment == Alignment::CENTER){
        x = cx - (width / 2);
    }
    else x += container.left;

    _computedDims.left = x;
    _computedDims.top = y;
    _computedDims.right = x + width;
    _computedDims.bottom = y + height;
    _computedDims = clampRect(container, _computedDims);
    return _computedDims;
}

void LayoutItem::_calculateLayoutChildren (LayoutState& state, const Rect& container) {
    if (_layoutFn) {
        _layoutFn(_computedDims, _layout, _children);
    }
}


Rect LayoutItem::calculateLayout (const Rect& container) {
    LayoutState state;
    _calculateLayoutSelf(state, container);
    _calculateLayoutChildren(state, container);
}

Rect LayoutItem::calculateLayout (uint32_t width, uint32_t height){
    Rect rect;
    rect.right = width;
    rect.bottom = height;
    calculateLayout(rect);
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