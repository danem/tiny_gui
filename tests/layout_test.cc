#include <tiny_gui/tiny_gui.h>
#include <tiny_gui/linked_list.h>
#include <stdio.h>

int main () {
    tiny_gui::LayoutItem root{
        tiny_gui::LayoutBuilder()
            .dimensions_relative(1,1),
        tiny_gui::VerticalLayout
    };


    tiny_gui::LayoutItem pane1 {
        tiny_gui::LayoutBuilder()
            .dimensions_relative(1, 0.5),
        tiny_gui::HorizontalLayout
    };

    tiny_gui::LayoutItem pane2 {
        tiny_gui::LayoutBuilder()
            .dimensions_relative(1, 0.5),
        tiny_gui::VerticalLayout
    };

    tiny_gui::LayoutItem h1 {
        tiny_gui::LayoutBuilder()
            .dimensions_relative(0.3, 1)
    };

    tiny_gui::LayoutItem h2 {
        tiny_gui::LayoutBuilder()
            .size_policy(tiny_gui::SizePolicy::STRETCH, tiny_gui::SizePolicy::NONE)
            .dimensions_relative(0, 1)
    };

    tiny_gui::LayoutItem h3 {
        tiny_gui::LayoutBuilder()
            .size_policy(tiny_gui::SizePolicy::STRETCH, tiny_gui::SizePolicy::NONE)
            .dimensions_relative(0, 1)
    };

    tiny_gui::LayoutItem h4 {
        tiny_gui::LayoutBuilder()
            .dimensions_relative(0.3, 1)
    };

    tiny_gui::LayoutItem v1 {
        tiny_gui::LayoutBuilder()
            .size_policy(tiny_gui::SizePolicy::NONE, tiny_gui::SizePolicy::STRETCH)
            .dimensions_relative(1, 0)
    };

    tiny_gui::LayoutItem v2 {
        tiny_gui::LayoutBuilder()
            .size_policy(tiny_gui::SizePolicy::NONE, tiny_gui::SizePolicy::STRETCH)
            .dimensions_relative(1, 0)
    };

    tiny_gui::LayoutItem v3 {
        tiny_gui::LayoutBuilder()
            .size_policy(tiny_gui::SizePolicy::NONE, tiny_gui::SizePolicy::STRETCH)
            .dimensions_relative(1,0)
    };

    tiny_gui::LayoutItem v4 {
        tiny_gui::LayoutBuilder()
            .size_policy(tiny_gui::SizePolicy::NONE, tiny_gui::SizePolicy::STRETCH)
            .dimensions_relative(1, 0)
    };

    root.addChild(pane1);
    pane1.addChild(h1);
    pane1.addChild(h2);
    pane1.addChild(h3);
    pane1.addChild(h4);

    root.addChild(pane2);
    pane2.addChild(v1);
    pane2.addChild(v2);
    pane2.addChild(v3);
    pane2.addChild(v4);

    root.calculateLayout(100,100);


    assert(pane1._computedDims.width() == 100);
    assert(pane1._computedDims.height() == 50);
    assert(pane1._computedDims.top == 0);

    assert(h1._computedDims.width() == 30);
    assert(h1._computedDims.left == 0);

    assert(h2._computedDims.width() == 20);
    assert(h2._computedDims.left == 30);

    assert(h3._computedDims.width() == 20);
    assert(h3._computedDims.left == 50);

    assert(h4._computedDims.width() == 30);
    assert(h4._computedDims.left == 70);

    assert(pane2._computedDims.width() == 100);
    assert(pane2._computedDims.height() == 50);
    assert(pane2._computedDims.top == 50);

    printf("%d\n", v3._computedDims.height());
    assert(v1._computedDims.height() == 12);
    assert(v1._computedDims.top == 50);

    assert(v2._computedDims.height() == 12);
    assert(v2._computedDims.top == 50 + (12*1));

    assert(v3._computedDims.height() == 12);
    assert(v3._computedDims.top == 50 + (12*2));

    assert(v4._computedDims.height() == 12);
    assert(v4._computedDims.top == 50 + (12*3));



    printf("Layout Tests Passed\n");
}