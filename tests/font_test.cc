#define TINY_GUI_COLOR_ABGR
#include <SimpleGL/helpers/SimpleGLHelpers.h>
#include <tiny_gui/tiny_gui.h>
#include <tiny_gui/font.h>
#include <array>

#include "font.h"



#define DATA_FILE(f) (SYNTH_DATA_DIR "/" f)

int main () {
    std::array<uint32_t, 500*500> frame_buffer = {0};
    tiny_gui::FrameBuffer fb{frame_buffer.data(), 500, 500};
    tiny_gui::FrameBufferView fbv = fb.view();

    sgl::Context ctx{500,500,"Foo"};
    sgl::MeshResource plane =  sgl::createPlane(1);
    sgl::Shader shader = sgl::loadShader(DATA_FILE("ident_vs.glsl"), DATA_FILE("texture_fs.glsl"));

    sgl::Texture2D fb_tx = sgl::TextureBuilder2D()
        .format(GL_RGBA, GL_RGBA8)
        .build(500, 500);
    
    tiny_gui::Painter::draw_char(fb, RobotoRegular8Font, tiny_gui::RED, 200, 200, 'A');
    tiny_gui::Painter::draw_string(fb, RobotoRegular8Font, tiny_gui::RED, 200, 300, "Hello!");

    int x = 0;
    tiny_gui::Rect clearRect;
    
    while (ctx.isAlive()){
        glClear(GL_COLOR_BUFFER_BIT);
        ctx.pollEvents();

        x += 1;
        std::string num = std::to_string(x);
        tiny_gui::Rect r = tiny_gui::Painter::get_text_bounds(RobotoRegular8Font, 200, 400, num);
        tiny_gui::Painter::fill_rect(fb, r, tiny_gui::BLUE);
        tiny_gui::Painter::draw_string(fb, RobotoRegular8Font, tiny_gui::RED, 200, 400, num);

        sgl::updateTexture(fb_tx, frame_buffer.data());

        shader.bind();
        shader.setTexture("image", fb_tx, 0);

        plane.bind();
        glDrawElements(GL_TRIANGLES, plane.size, GL_UNSIGNED_INT, 0);
        ctx.swapBuffers();
        sglCatchGLError();
    }

}
