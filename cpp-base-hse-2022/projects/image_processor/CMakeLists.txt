cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(MY_PROJECT_FILES
        Image.cpp Image.h
        Reader.cpp Reader.h
        Writer.cpp Writer.h
        Filters/Filter.cpp Filters/Filter.h
        Filters/GrayScale.cpp Filters/GrayScale.h
        Filters/Negative.cpp Filters/Negative.h
        Filters/Sharpening.cpp Filters/Sharpening.h
        Filters/EdgeDetection.cpp Filters/EdgeDetection.h
        Filters/GaussianBlur.cpp Filters/GaussianBlur.h
        Filters/Relief.cpp Filters/Relief.h
        Filters/Crop.cpp Filters/Crop.h
        Filters/MatrixFilter.cpp Filters/MatrixFilter.h
        BMP.cpp BMP.h Filters/Mosaic.cpp Filters/Mosaic.h)

add_executable(image_processor
        ${MY_PROJECT_FILES}
        image_processor.cpp
        )


function(create_test test_name)
    add_executable(${test_name}
            ${MY_PROJECT_FILES}
            tests/${test_name}.cpp
            )
    target_include_directories(${test_name} PUBLIC .)
    add_test(${test_name} ${test_name})
endfunction()


enable_testing()

create_test(test_read_write)
create_test(test_building)
create_test(test_image)
create_test(test_crop)
create_test(test_grayscale)
create_test(test_negative)
create_test(test_sharpening)
create_test(test_edge_detection)
create_test(test_gaussian_blur)
create_test(test_relief)
create_test(test_mosaic)
