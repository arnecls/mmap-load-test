#include "file_buffer.h"
#include <cstdio>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <cerrno>
#include <cstdio>
#include <sys/mman.h>
#include <sys/stat.h>

FileBuffer::FileBuffer(const std::string& aFileName) {
    char buffer[1024] = {0};
    
    mFileHandle = ::open(aFileName.c_str(),O_RDONLY);
    if (mFileHandle < 0) {
        ::snprintf(buffer, sizeof(buffer), "Error opening file %s: %s", aFileName.c_str(), strerror(errno));
        throw FileException(buffer);
    }
    
    struct ::stat stats;
    ::fstat(mFileHandle, &stats);
    mSize = stats.st_size;
    
    mpData = (uint8_t*)::mmap(NULL, mSize, PROT_READ, MAP_PRIVATE|MAP_FILE, mFileHandle, 0);
    if (mpData == MAP_FAILED) {
        close(mFileHandle);
        ::snprintf(buffer, sizeof(buffer), "Error mapping file %s: %s", aFileName.c_str(), strerror(errno));
        throw FileException(buffer);
    }
}

FileBuffer::~FileBuffer() {
    ::munmap(mpData, mSize);
    ::close(mFileHandle);
}

void* PosixLoad(const char* aFileName) {
     struct ::stat stats;
    
    auto fd = ::fopen(aFileName, "r");
    ::stat(aFileName, &stats);
    
    auto buffer = ::malloc(stats.st_size);
    ::fread(buffer, stats.st_size, 1, fd);
    ::fclose(fd);
    
    return buffer;
}
