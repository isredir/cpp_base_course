#include "Filter.h"
void Filter::IsValid(int argc, const char *argv[], int& pos) {
    if (pos + args >= argc) {
        throw std::runtime_error{"not enough arguments for filter"};
    }
    try{
        for (int i = 1; i <= args; ++i) {
            float float_arg = std::stof(argv[pos + i]);
            int int_arg = std::stoi(argv[pos + i]);
        }
    } catch (std::invalid_argument) {
        throw std::runtime_error{"invalid argument for filter"};
    }
}
