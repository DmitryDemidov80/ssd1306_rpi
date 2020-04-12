cmake_minimum_required(VERSION 3.8)

project(examples_ssd1306_rpi)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(
    -Wall
    -Wfloat-equal
    -Wimplicit-fallthrough
    -Wunreachable-code
    -D_FILE_OFFSET_BITS=64
)


add_executable(${PROJECT_NAME}
    main.cpp
    ../ssd1306_rpi_i2c.cpp
    )

target_link_libraries(${PROJECT_NAME} pthread)

#add_library(${PROJECT_NAME}
#    )
