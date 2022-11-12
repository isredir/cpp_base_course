#pragma once
#include "Image.h"

class Writer {
public:
    Writer(const char* path);
    void Export(const Image& image);
private:
    const char* path_;
};

