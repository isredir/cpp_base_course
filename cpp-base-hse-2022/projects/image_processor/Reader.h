#pragma once
#include "Image.h"

class Reader {
public:
    Reader(const char* path);
    Image Read();
private:
    const char* path_;
};


