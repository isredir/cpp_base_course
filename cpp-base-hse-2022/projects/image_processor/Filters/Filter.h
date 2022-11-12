#pragma once
#include "../Image.h"

class Filter {
public:
    virtual void ApplyFilter(Image& image, int argc, const char *argv[], int& pos) = 0;
    virtual void IsValid(int argc, const char *argv[], int& pos);

protected:
    int args = 0;
};
