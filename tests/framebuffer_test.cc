#include <tiny_gui/tiny_gui.h>
#include <array>
#include <stdint.h>

int main () {
    std::array<uint16_t,500 * 500> data;
    data[500 * 50 + 66] = 99;
    data[500 * 55 + 32] = 99;

    tiny_gui::FrameBuffer fb{data.data(), 500, 500};
    auto fbv = fb.view<uint16_t>();
    auto fbv2 = fb.view<uint16_t>(10,10);

    assert(fbv.row(50)[66] == 99);
    assert(fbv2.row(45)[22] == 99);
}