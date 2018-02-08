#pragma once

#include <exception>

class FileException : public std::exception {
private:
    std::string mMessage;
    
public:
    inline FileException(const std::string& aMessage);
    inline const std::string& message() const;
};

#include "file_exception.hpp"
