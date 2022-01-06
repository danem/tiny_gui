#include <tiny_gui/linked_list.h>
#include <iostream>

struct Foo {
    int a;
    tiny_gui::list_head list;
    Foo (int v) : a(v) {}
};

int main () {
    Foo a{1};
    Foo b{2};
    Foo c{3};
    tiny_gui::list_append(a.list, b.list);
    tiny_gui::list_append(a.list, c.list);
    for (tiny_gui::list_head& item : tiny_gui::list_iterator{a.list}){
        std::cout << list_entry(&item, Foo, list)->a << std::endl;
    }
    std::cout << tiny_gui::list_length(a.list) << std::endl;
}