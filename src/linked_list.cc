#include <tiny_gui/linked_list.h>

namespace tiny_gui {

// TODO: Doesn't account for loops.

void list_add (list_head& list, list_head& item) {
    list.next = &item;
}

uint32_t list_length (const list_head& list) {
    uint32_t count = 1;
    list_head* node = list.next;
    while (node) {
        count += 1;
        node = node->next;
    }
    return count;
}

void list_append (list_head& list, list_head& item) {
    list_head* node = &list;
    while (node->next) {
        node = node->next;
    }
    node->next = &item;
}

list_head* list_index (list_head& list, uint32_t index) {
    // No bounds checking
    list_head* node = &list;
    while (node && index) {
        index -= 1;
        node = node->next;
    }
    return node;
}

} // end namespace