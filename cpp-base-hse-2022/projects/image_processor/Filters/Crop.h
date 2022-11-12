#pragma once
#include "Filter.h"

class Crop : public Filter {
public:
    void ApplyFilter(Image& image, int argc, const char *argv[], int& pos) override;
};
