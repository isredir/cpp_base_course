#include <iostream>
#include "Image.h"
#include "Reader.h"
#include "Writer.h"

int main() {
    Reader reader("../examples/example.bmp");
    Image example(0, 0);
    example = reader.Read();
    Writer writer("../examples/example_output.bmp");
    writer.Export(example);
    Reader reader2("../examples/example_output.bmp");
    Image example_copy = reader2.Read();
    if (example_copy != example) {
        std::cerr << "Test for \"reading and writing\" failed..." << std::endl;
        return 1;
    }
    return 0;
}
