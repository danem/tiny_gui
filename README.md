## Tiny GUI

-----------

Extremely lightweight GUI, with a focus on simplicity and flexibility for embedded devices.
Tiny GUI aims to be more powerful and flexible than libraries like AdafruitGFX, while being lighter than
lvgl, guilite, imgui, etc.

* <15kb
* <2000 lines of code

### Features
* No dependencies
* Extremely portable
* No dynamic memory management
* Rudimentary drawing
    * Draw to memory or directly to display
* Font + bitmap rendering
* Rudimentary layout engine
    * Relative sizing + positioning
    * Various layouts (Vertical, Horizontal, Grid)
* Widgets

### Basic Usage
```c++
#include <tiny_gui/tiny_gui.h>

int main () {
    std::array<uint32_t, WIDTH*HEIGHT> frame_data;
    tiny_gui::FrameBuffer fb{frame_data.data(), WIDTH, HEIGHT};
    tiny_gui::Painter::draw_rect(fb, {0, 10, 0, 10}, tiny_gui::RED);

    your_draw_pixels_to_screen_fn(frame_data);
}
```

### Widget Usage
```c++
#include <tiny_gui/tiny_gui.h>

int main () {
    std::array<uint32_t, WIDTH*HEIGHT> frame_data;
    tiny_gui::FrameBuffer fb{frame_data.data(), WIDTH, HEIGHT};

    tiny_gui::Style button_style = tiny_gui::StyleBuilder()
        .set_font(&RobotoRegular8Font)
        .button_color(tiny_gui::RED, tiny_gui::BLUE, {0}, tiny_gui::GREEN);
    
    tiny_gui::PushButton button_widget{button_style, "Click me"};
    tiny_gui::LayoutItem button_item{
        button_widget,
        tiny_gui::LayoutBuilder()
            .dimensions_relative(0.25,0.25)
            .alignment(tiny_gui::ALIGNMENT::CENTER, tiny_gui::ALIGNMENT::CENTER)
    };

    tiny_gui::LayoutItem root{tiny_gui::LayoutBuilder().dimensions_relative(1,1)};
    root.addChild(button_item);
    root.calculateLayout(WIDTH,HEIGHT);
    root.render(fb);

    your_draw_pixels_to_screen_fn(frame_data);
}
```

### Building
Tiny GUI itself has no dependencies, but the example programs use [SimpleGL](https://github.com/danem/simplegl) for rendering on desktop. Enable/Disable the example programs by setting `-DBUILD_EXAMPLES=OFF` if you don't wish to install it.

```
cd tiny_gui
mkdir build
cd build
cmake -DBUILD_EXAMPLES=OFF -DBUILD_TYPE=MinSizeRel ..
make
```