#pragma once

inline FileException::FileException(const std::string& aMessage)
: mMessage(aMessage)
{
}

inline const std::string& FileException::message() const {
    return mMessage;
}
