#define TINY_GUI_COLOR_ABGR
#include <SimpleGL/helpers/SimpleGLHelpers.h>
#include <tiny_gui/tiny_gui.h>
#include <tiny_gui/font.h>
#include <array>

#include "font.h"



#define DATA_FILE(f) (SYNTH_DATA_DIR "/" f)

int main () {
    std::array<uint32_t, 500*500> frame_buffer = {0};
    tiny_gui::FrameBufferMemory fb{frame_buffer.data(), 500, 500};

    sgl::Context ctx{500,500,"Foo"};
    sgl::MeshResource plane =  sgl::createPlane(1);
    sgl::Shader shader = sgl::loadShader(DATA_FILE("ident_vs.glsl"), DATA_FILE("texture_fs.glsl"));

    sgl::Texture2D fb_tx = sgl::TextureBuilder2D()
        .format(GL_RGBA, GL_RGBA8)
        .build(500, 500);

    // Test font search
    tiny_gui::Glyph glyph;
    assert(tiny_gui::getGlyph(HelveticaBold12Font, 'z', glyph));
    assert(tiny_gui::getGlyph(HelveticaBold5Font, 'a', glyph));
    assert(tiny_gui::getGlyph(HelveticaBold5Font, 'z', glyph));
    assert(!tiny_gui::getGlyph(HelveticaBold5Font, '$', glyph));
    
    // Test Font Rendering
    tiny_gui::Rect rect; 
    rect = tiny_gui::Painter::draw_string(fb, HelveticaBold12Font, tiny_gui::WHITE, 10, 30, "abcdefghijklmnopqrstuvwxyz");
    rect = tiny_gui::Painter::draw_string(fb, HelveticaBold12Font, tiny_gui::WHITE, 10, rect.bottom+30, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    rect = tiny_gui::Painter::draw_string(fb, HelveticaBold12Font, tiny_gui::WHITE, 10, rect.bottom+30, "0123456789");
    rect = tiny_gui::Painter::draw_string(fb, HelveticaBold7Font, tiny_gui::WHITE, 10, rect.bottom+20, "abcdefghijklmnopqrstuvwxyz");
    rect = tiny_gui::Painter::draw_string(fb, HelveticaBold7Font, tiny_gui::WHITE, 10, rect.bottom+20, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    rect = tiny_gui::Painter::draw_string(fb, HelveticaBold7Font, tiny_gui::WHITE, 10, rect.bottom+20, "0123456789");
    rect = tiny_gui::Painter::draw_string(fb, HelveticaBold5Font, tiny_gui::WHITE, 10, rect.bottom+15, "abcdefghijklmnopqrstuvwxyz");
    rect = tiny_gui::Painter::draw_string(fb, HelveticaBold5Font, tiny_gui::WHITE, 10, rect.bottom+15, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    rect = tiny_gui::Painter::draw_string(fb, HelveticaBold5Font, tiny_gui::WHITE, 10, rect.bottom+15, "0123456789");
    rect = tiny_gui::Painter::draw_string(fb, RobotoRegular8Font, tiny_gui::WHITE, 10, rect.bottom+15, "abcdefghijklmnopqrstuvwxyz");
    rect = tiny_gui::Painter::draw_string(fb, RobotoRegular8Font, tiny_gui::WHITE, 10, rect.bottom+15, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    rect = tiny_gui::Painter::draw_string(fb, RobotoRegular8Font, tiny_gui::WHITE, 10, rect.bottom+15, "0123456789");
    rect = tiny_gui::Painter::draw_string(fb, RobotoRegular14Font, tiny_gui::WHITE, 10, rect.bottom+30, "abcdefghijklmnopqrstuvwxyz");
    rect = tiny_gui::Painter::draw_string(fb, RobotoRegular14Font, tiny_gui::WHITE, 10, rect.bottom+30, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    rect = tiny_gui::Painter::draw_string(fb, RobotoRegular14Font, tiny_gui::WHITE, 10, rect.bottom+30, "0123456789");

    int y = rect.bottom + 30;
    rect = tiny_gui::Painter::draw_string(fb, HelveticaBold5Font, tiny_gui::WHITE, 10, y, "Zz");
    rect = tiny_gui::Painter::draw_string(fb, HelveticaBold7Font, tiny_gui::WHITE, rect.right + 5, y, "Zz");
    rect = tiny_gui::Painter::draw_string(fb, HelveticaBold12Font, tiny_gui::WHITE, rect.right + 5, y, "Zz");
    rect = tiny_gui::Painter::draw_string(fb, RobotoRegular8Font, tiny_gui::WHITE, rect.right + 5, y, "Zz");
    rect = tiny_gui::Painter::draw_string(fb, RobotoRegular14Font, tiny_gui::WHITE, rect.right + 5, y, "Zz");



    int x = 0;
    tiny_gui::Rect clearRect;
    
    while (ctx.isAlive()){
        glClear(GL_COLOR_BUFFER_BIT);
        ctx.pollEvents();

        x += 1;
        std::string num = std::to_string(x);
        tiny_gui::Rect r;
        r = tiny_gui::Painter::get_text_bounds(RobotoRegular8Font, 200, 400, num);
        tiny_gui::Painter::fill_rect(fb, r, tiny_gui::BLUE);
        tiny_gui::Painter::draw_string(fb, RobotoRegular8Font, tiny_gui::RED, 200, 400, num);

        r = tiny_gui::Painter::get_text_bounds(HelveticaBold12Font, 200, 450, num);
        tiny_gui::Painter::fill_rect(fb, r, tiny_gui::BLUE);
        tiny_gui::Painter::draw_string(fb, HelveticaBold12Font, tiny_gui::RED, 200, 450, num);

        sgl::updateTexture(fb_tx, frame_buffer.data());

        shader.bind();
        shader.setTexture("image", fb_tx, 0);

        plane.bind();
        glDrawElements(GL_TRIANGLES, plane.size, GL_UNSIGNED_INT, 0);
        ctx.swapBuffers();
        sglCatchGLError();
    }

}
