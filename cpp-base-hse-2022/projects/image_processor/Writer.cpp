#include <fstream>
#include <iostream>
#include "Writer.h"

template<typename T>
void WriteValue(std::ofstream& output, T value) {
    unsigned char buffer[sizeof(value)];
    std::make_unsigned_t<T> x = value;
    for (size_t i = 0; i < sizeof(value); ++i) {
        buffer[i] = x >> (8 * i);
    }
    output.write(reinterpret_cast<char *>(buffer), sizeof(value));
}

Writer::Writer(const char *path) : path_(path) {
}

void Writer::Export(const Image &image) {
    std::ofstream output{ path_, std::ios_base::binary };
    if (!output.is_open()) {
        throw std::runtime_error{"error opening file"};
    }
    BMP header;
    char bmp_pad[3] = {0, 0, 0};
    const int file_header_size = 14;
    const int info_header_size = 40;
    const int padding_amount = ((4 - (header.info_header.width * 3) % 4) % 4);
    header.file_header.file_size = file_header_size + info_header_size + image.GetWidth() * image.GetHeight() * 3 +
                                   padding_amount * image.GetHeight();
    header.file_header.offset_data = file_header_size + info_header_size;
    header.info_header.size = info_header_size;
    header.info_header.width = image.GetWidth();
    header.info_header.height = image.GetHeight();

    WriteValue(output, header.file_header.file_type);
    WriteValue(output, header.file_header.file_size);
    WriteValue(output, header.file_header.reserved1);
    WriteValue(output, header.file_header.reserved2);
    WriteValue(output, header.file_header.offset_data);

    WriteValue(output, header.info_header.size);
    WriteValue(output, header.info_header.width);
    WriteValue(output, header.info_header.height);
    WriteValue(output, header.info_header.planes);
    WriteValue(output, header.info_header.bit_count);
    WriteValue(output, header.info_header.compression);
    WriteValue(output, header.info_header.size_image);
    WriteValue(output, header.info_header.x_pixels_per_meter);
    WriteValue(output, header.info_header.y_pixels_per_meter);
    WriteValue(output, header.info_header.colors_used);
    WriteValue(output, header.info_header.colors_important);

    for (int y = 0; y < header.info_header.height; ++y) {
        for (int x = 0; x < header.info_header.width; ++x) {
            unsigned char r = static_cast<unsigned char>(image.At(x, y).r * 255.0f);
            unsigned char g = static_cast<unsigned char>(image.At(x, y).g * 255.0f);
            unsigned char b = static_cast<unsigned char>(image.At(x, y).b * 255.0f);
            unsigned char color[] = {b, g, r};
            output.write(reinterpret_cast<char *>(color), 3);
        }
        output.write(bmp_pad, padding_amount);
    }
}
