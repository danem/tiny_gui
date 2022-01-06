#pragma once

#include <stdint.h>
#include <cstddef>

namespace tiny_gui {

template <class T>
class dynamic_array {
private:
    T* _data;
    std::size_t _size;

public:
    dynamic_array (T* data, std::size_t size) :
        _data(data),
        _size(size)
    {}

    T* data () {
        return _data;
    }

    const T* constData(){
        return _data;
    }

    std::size_t size () {
        return _size;
    }

    T& operator[](std::size_t idx) {
        return _data[idx];
    }

    struct Iterator {
    private:
        T* _data;

    public:
        Iterator (T* data) : _data(data) {}

        Iterator& operator++(){
            _data += 1;
            return *this;
        }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a._data == b._data; }
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a._data != b._data; }

        T* operator->() { return _data; }
        T& operator*() { return *_data; }
    };

    Iterator begin () { return {_data}; }
    Iterator end () { return { _data + _size }; }

};


} // end namespace