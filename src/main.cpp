#include <cstdio>
#include <thread>
#include <cmath>
#include <time.h>
#include <unistd.h>

#include "file_buffer.h"
#include "timer.h"

const long microseconds = 1000;
const long milliseconds = 1000 * microseconds;

const size_t kilobyte = 1024;
const size_t megabyte = 1024 * kilobyte;
const size_t gigabyte = 1024 * megabyte;

const ::timespec sleepPrint = {
    .tv_sec  = 0,
    .tv_nsec = 200*milliseconds
};
const ::timespec sleepNoFile = {
    .tv_sec  = 1,
    .tv_nsec = 0
};

int main(int argc, char** argv) {
    std::mutex readGuard;
    std::shared_ptr<FileBuffer> pFile;
    bool stop = false;
    
    // Printer thread. This loop prints the contents of the file
    auto printer = std::thread([&](){
        while (!stop) {
            if (pFile == nullptr) {
                ::nanosleep(&sleepNoFile, nullptr);
                continue;
            }
            
            std::lock_guard<std::mutex> g(readGuard);
            
            auto rnd = size_t((::rand() / float(RAND_MAX)) * pFile->size());
            ::printf("%d ",(*pFile)[rnd]);
            ::nanosleep(&sleepPrint, nullptr);
        }
    });
    
    ::printf("Press 1 to load 1.raw (4GB zeros)\n");
    ::printf("Press 2 to load 2.raw (4GB random)\n");
    ::printf("Press 3 to load 3.raw (8GB random)\n");
    ::printf("Press p to time a posix load of 2.raw\n");
    ::printf("Press q to quit\n");
    
    try {
        system("stty raw"); // So we don't need to press enter after every keystroke
        while (!stop) {
            switch (getchar()) {
                case '1': {
                    std::lock_guard<std::mutex> g(readGuard);
                    ::fprintf(::stderr, "\nLoading 1.raw\n");
                    {
                        Timer t("Loading");
                        pFile = pFile.make_shared("1.raw"); // removes the old file
                    }
                    ::fprintf(::stderr, "Loaded %.2f GB\n", pFile->size() / float(gigabyte));
                    break;
                }
                    
                case '2': {
                    std::lock_guard<std::mutex> g(readGuard);
                    ::fprintf(::stderr, "\nLoading 2.raw\n");
                    {
                        Timer t("Loading");
                        pFile = pFile.make_shared("2.raw"); // removes the old file
                    }
                    ::fprintf(::stderr, "Loaded %.2f GB\n", pFile->size() / float(gigabyte));
                    break;
                }
                    
                case '3': {
                    std::lock_guard<std::mutex> g(readGuard);
                    ::fprintf(::stderr, "\nLoading 3.raw\n");
                    {
                        Timer t("Loading");
                        pFile = pFile.make_shared("3.raw"); // removes the old file
                    }
                    ::fprintf(::stderr, "Loaded %.2f GB\n", pFile->size() / float(gigabyte));
                    break;
                }
                    
                case 'p': {
                    if (pFile == nullptr) {
                        continue;
                    }
                    std::lock_guard<std::mutex> g(readGuard);
                    ::fprintf(::stderr, "\nLoading 4 GB using posix\n");
                    {
                        Timer t("Loading");
                        void* buffer = PosixLoad("2.raw");
                        ::free(buffer);
                    }
                    break;
                }
                    
                case 'q':
                    stop = true;
                    continue;
            }
        }
    }
    catch (const FileException& e) {
        ::printf("Exception: %s\n", e.message().c_str());
        stop = true;
    }
    catch (...) {
        stop = true;
    }
    
    ::fprintf(::stderr, "\nQuitting...\n");
    printer.join(); // make sure that the printer thread properly quit
    return 0;
}
