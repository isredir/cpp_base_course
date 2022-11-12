#pragma once
#include "Filter.h"

class Relief : public Filter {
public:
    void ApplyFilter(Image& image, int argc, const char *argv[], int& pos) override;
};
