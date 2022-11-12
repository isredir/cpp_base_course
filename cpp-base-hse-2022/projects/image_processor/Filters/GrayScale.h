#pragma once
#include "../Image.h"
#include "Filter.h"

class GrayScale : public Filter {
public:
    void ApplyFilter(Image& image, int argc, const char *argv[], int& pos) override;
};

