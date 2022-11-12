#include "Reader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

template<typename T>
void ReadValue(std::ifstream& input, T& value) {
    std::make_unsigned_t<T> x = 0;
    unsigned char buffer[sizeof(value)];
    input.read(reinterpret_cast<char *>(buffer), sizeof(value));
    for (size_t i = 0; i < sizeof(value); ++i) {
        x += buffer[i] << (8 * i);
    }
    value = static_cast<T>(x);
}

Reader::Reader(const char *path) : path_(path) {
}

Image Reader::Read() {
    std::ifstream input{path_, std::ios_base::binary};
    if (!input.is_open()) {
        throw std::runtime_error{"error opening file"};
    }
    BMP header;
    ReadValue(input, header.file_header.file_type);
    if (header.file_header.file_type != 0x4D42) {
        std::cout << header.file_header.file_type << " " << 0x4D42 << std::endl;
        throw std::runtime_error{"not a bmp"};
    }
    ReadValue(input, header.file_header.file_size);
    ReadValue(input, header.file_header.reserved1);
    ReadValue(input, header.file_header.reserved2);
    ReadValue(input, header.file_header.offset_data);

    ReadValue(input, header.info_header.size);
    ReadValue(input, header.info_header.width);
    ReadValue(input, header.info_header.height);
    ReadValue(input, header.info_header.planes);
    ReadValue(input, header.info_header.bit_count);
    ReadValue(input, header.info_header.compression);
    ReadValue(input, header.info_header.size_image);
    ReadValue(input, header.info_header.x_pixels_per_meter);
    ReadValue(input, header.info_header.y_pixels_per_meter);
    ReadValue(input, header.info_header.colors_used);
    ReadValue(input, header.info_header.colors_important);

    Image image = {header.info_header.width, header.info_header.height};
    const int padding_amount = ((4 - (header.info_header.width * 3) % 4) % 4);
    for (int y = 0; y < header.info_header.height; ++y) {
        for (int x = 0; x < header.info_header.width; ++x) {
            unsigned char color[3] = {0, 0, 0};
            input.read(reinterpret_cast<char *>(color), 3);
            float rr = static_cast<float>(color[2]) / 255.0f;
            float gg = static_cast<float>(color[1]) / 255.0f;
            float bb = static_cast<float>(color[0]) / 255.0f;
            image.At(x, y) = {rr, gg, bb};
        }
        input.ignore(padding_amount);
    }
    return image;
}