#include "file_exception.h"

inline uint8_t FileBuffer::operator[] (size_t aIndex) const {
    if (aIndex >= mSize) {
        throw FileException("Offset out of bounds.");
    }
    return mpData[aIndex];
}

inline size_t FileBuffer::size() {
    return mSize;
}
