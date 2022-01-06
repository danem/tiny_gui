#pragma once
#include <stdint.h>

// Intrusive linked list based on Linux kernel approach
//
// Macros like this are kinda gross, but if it's good
// enough for the linux kernel...
// 
// Despite being less intuitive, intrusive lists have a number of benefits.
// Most importantly, they require no memory allocations

// ------------------



#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

/** 
* list_entry - get the struct for this entry 
* @ptr:        the &struct list_head pointer. 
* @type:       the type of the struct this is embedded in. 
* @member:     the name of the list_struct within the struct. 
*/ 
#define list_entry(ptr, type, member)\
    container_of(ptr, type, member)


// TODO: Is this portable??
/** 
* container_of - cast a member of a structure out to the containing structure 
* @ptr:        the pointer to the member. 
* @type:       the type of the container struct this is embedded in. 
* @member:     the name of the member within the struct. 
* 
*/ 
#define container_of(ptr, type, member) ({\
    const typeof( ((type *)0)->member ) *__mptr = (ptr);\
    (type *)( (char *)__mptr - offsetof(type,member) );}) 


namespace tiny_gui {

struct list_head {
    list_head* next;
};

class list_iterator {
private:
    list_head* _list;
public:
    list_iterator (list_head* list) : _list(list) {}
    list_iterator (list_head& list) : _list(&list) {}

    list_iterator& operator++(){
        _list = _list->next;
        return *this;
    }

    friend bool operator== (const list_iterator& a, const list_iterator& b) { return a._list == b._list; }
    friend bool operator!= (const list_iterator& a, const list_iterator& b) { return a._list != b._list; }

    list_head* operator->() { return _list; }
    list_head& operator*() { return *_list; }

    list_iterator begin () { return *this; }
    list_iterator end () { return {nullptr}; }
};


// Set the next pointer to the supplied list.
// Removes whatever was previously there.
void list_add (list_head& list, list_head& item);

uint32_t list_length (const list_head& list);
void list_append (list_head& list, list_head& item);
list_head* list_index (list_head& list, uint32_t index);




} // end namespace