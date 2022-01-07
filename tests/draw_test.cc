#define TINY_GUI_COLOR_ABGR
#include <SimpleGL/helpers/SimpleGLHelpers.h>
#include <tiny_gui/tiny_gui.h>
#include <array>
#include <stdio.h>


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
    
    tiny_gui::Painter::fill_color(fb, tiny_gui::BLUE);
    tiny_gui::Painter::draw_rect(fb, {250, 350, 100, 200}, tiny_gui::WHITE);
    tiny_gui::Painter::fill_rect(fb, {150, 200, 50, 100}, tiny_gui::RED);
    
    while (ctx.isAlive()){
        glClear(GL_COLOR_BUFFER_BIT);
        ctx.pollEvents();

        sgl::updateTexture(fb_tx, frame_buffer.data());

        shader.bind();
        shader.setTexture("image", fb_tx, 0);

        plane.bind();
        glDrawElements(GL_TRIANGLES, plane.size, GL_UNSIGNED_INT, 0);


        ctx.swapBuffers();
        sglCatchGLError();
    }
}