#include <string>
#include <stdint.h>

class FileBuffer {
private:
    int     mFileHandle;
    uint8_t *mpData;
    size_t  mSize;
    
public:
    FileBuffer(const std::string& aFileName);
    ~FileBuffer();
    
    FileBuffer(const FileBuffer&) = delete;
    FileBuffer& operator=(const FileBuffer&) = delete;
    
public:
    
    inline uint8_t operator[] (size_t aIndex) const;
    inline size_t size();
};

void* PosixLoad(const char* aFileName);

#include "file_buffer.hpp"
