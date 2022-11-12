#pragma once
#include "Filter.h"

class GaussianBlur : public Filter {
public:
    void ApplyFilter(Image& image, int argc, const char *argv[], int& pos) override;
};
