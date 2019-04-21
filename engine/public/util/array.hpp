#pragma once

#include <core/data_types.hpp>
#include <core/debug.hpp>
#include <util/memory.hpp>
#include <algorithm>

namespace ENGH::Util {

template<typename T>
class TArray {

    T *arr;
    uint16 len;
    uint16 cap;

public:

    constexpr TArray() :
            arr(nullptr),
            len(0),
            cap(0) {}

    constexpr TArray(std::initializer_list<T> elements) :
            arr(new T[elements.size()]),
            len(elements.size()),
            cap(elements.size()) {
        Memory::copy(elements.begin(), elements.end(), arr);
    }

    constexpr TArray(const TArray<T> &other) :
            arr(new T[other.len]),
            len(other.len),
            cap(other.cap) {
        Memory::copy(other.arr, arr, len);
    }

    constexpr TArray(TArray<T> &&other) noexcept :
            arr(other.arr),
            len(other.len),
            cap(other.cap) {
        other.arr = nullptr;
        other.len = other.cap = 0;
    }

    ~TArray() {
        delete arr;
    }

    constexpr T &operator[](uint16 index) const {
#ifdef ENGH_DEBUG
        if (index >= len) { // IndexOutOfBound Exception
            BREAK();
        }
#endif
        return arr[index];
    }

    constexpr uint16 length() const {
        return len;
    }

    constexpr uint16 capacity() const {
        return cap;
    }

    constexpr TArray &insert(T &&value) {
        if (len == cap) {
            reserve(1);
#ifdef ENGH_DEBUG
            if (arr == nullptr) { // OutOfMemory Exception
                BREAK();
            }
#endif
        }
        arr[len++] = value;
        return *this;
    }

    constexpr TArray &reserve(uint16 size) {
        arr = reinterpret_cast<T *>(std::realloc(arr, sizeof(T) * (cap += size)));
        return *this;
    }

};

}