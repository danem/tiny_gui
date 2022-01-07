#include <tiny_gui/tiny_gui.h>
#include <tiny_gui/linked_list.h>
#include <tiny_gui/layout.h>
#include <stdio.h>
#include "font.h"

#include <SimpleGL/helpers/SimpleGLHelpers.h>
#include <array>

#define DATA_FILE(f) (SYNTH_DATA_DIR "/" f)

tiny_gui::Style _button_style = tiny_gui::StyleBuilder()
    .set_font(&RobotoRegular8Font, tiny_gui::WHITE)
    .button_color(tiny_gui::RED, tiny_gui::BLUE, {0}, tiny_gui::GREEN)
    .build();
tiny_gui::Container _dividerWidget{tiny_gui::WHITE};
tiny_gui::Container _headerBG{{0xFF520928}};
tiny_gui::PushButton _button1{_button_style, "Button 1"};
tiny_gui::PushButton _button2{_button_style, "Button 2"};
tiny_gui::PushButton _button3{_button_style, "Button 3"};
tiny_gui::LayoutItem _root{tiny_gui::LayoutBuilder().dimensions_relative(1,1), tiny_gui::VerticalLayout};
tiny_gui::LayoutItem _header{_headerBG, tiny_gui::LayoutBuilder().dimensions_relative(1,0.05)};
tiny_gui::LayoutItem _pane1{tiny_gui::LayoutBuilder().dimensions_relative(1,0.75)};
tiny_gui::LayoutItem _divider{_dividerWidget, tiny_gui::LayoutBuilder().dimensions(tiny_gui::Measurement::R(1), tiny_gui::Measurement::A(1))};
tiny_gui::LayoutItem _pane2{tiny_gui::LayoutBuilder()
    .dimensions_relative(1,0.20)
    .spacing(5), 
    tiny_gui::HorizontalLayout
};

tiny_gui::LayoutProperties _button_layout = tiny_gui::LayoutBuilder()
    .dimensions_relative(0.3,0.7)
    .vertical_alignment(tiny_gui::Alignment::CENTER);

tiny_gui::LayoutItem _button1Item{_button1, _button_layout};
tiny_gui::LayoutItem _button2Item{_button2, _button_layout};
tiny_gui::LayoutItem _button3Item{_button3, _button_layout};

#define WIDTH 500
#define HEIGHT 350

void handleMouseEvent (tiny_gui::LayoutItem& layout, const sgl::MouseEvent& event){
    for(tiny_gui::list_head& list : tiny_gui::list_iterator{layout._children->_sibling_list}){
        tiny_gui::LayoutItem* item = list_entry(&list, tiny_gui::LayoutItem, _sibling_list);
        if (item->_computedDims.point_inside(event.x, event.y)){
            item->_widget->setMouseEventState(tiny_gui::MouseEventState::MOUSE_OVER);
        }
        else {
            item->_widget->setMouseEventState(tiny_gui::MouseEventState::NONE);
        }
    }
}


void drawWave (tiny_gui::FrameBuffer& fb, const tiny_gui::Rect& rect, int tick){
    tiny_gui::Painter::fill_rect(fb, rect, {static_cast<uint32_t>(tick)});
    /*
    for (int i = 0; i < rect.width(); i++){
        int py = static_cast<int>(rect.height() * std::sin(i + tick));
        tiny_gui::Painter::draw_pixel(fb, i+rect.left, py + rect.top, tiny_gui::WHITE);
    }
    */
}


int main () {
    std::array<uint32_t, WIDTH*HEIGHT> frame_buffer = {0};
    tiny_gui::FrameBufferMemory fb{frame_buffer.data(), WIDTH, HEIGHT};

    _root.addChild(_header);
    _root.addChild(_pane1);
    _root.addChild(_divider);
    _root.addChild(_pane2);
    _pane2.addChild(_button1Item);
    _pane2.addChild(_button2Item);
    _pane2.addChild(_button3Item);

    _root.calculateLayout(WIDTH, HEIGHT);
    _root.render(fb);


    sgl::Context ctx{WIDTH,HEIGHT,"Foo"};
    sgl::MeshResource plane =  sgl::createPlane(1);
    sgl::Shader shader = sgl::loadShader(DATA_FILE("ident_vs.glsl"), DATA_FILE("texture_fs.glsl"));

    sgl::Texture2D fb_tx = sgl::TextureBuilder2D()
        .format(GL_RGBA, GL_RGBA8)
        .build(WIDTH, HEIGHT);
    
    ctx.addMouseHandler([&fb](const sgl::MouseEvent& evt){
        handleMouseEvent(_pane2, evt);
        _pane2.render(fb);
    });
    
    int tick = 0; 
    while (ctx.isAlive()){
        glClear(GL_COLOR_BUFFER_BIT);
        ctx.pollEvents();

        drawWave(fb, _pane1._computedDims, tick);
        tick += 1;

        sgl::updateTexture(fb_tx, frame_buffer.data());


        shader.bind();
        shader.setTexture("image", fb_tx, 0);

        plane.bind();
        glDrawElements(GL_TRIANGLES, plane.size, GL_UNSIGNED_INT, 0);


        ctx.swapBuffers();
        sglCatchGLError();
    }
}