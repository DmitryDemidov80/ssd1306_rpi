cmake_minimum_required(VERSION 3.8)

project(ssd1306_rpi)
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)
set (VERSION_PATCH 0)
set (LIB_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
message("SSD1306_RPI_I2C VERSION: " ${LIB_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(
    -Wall
    -Wfloat-equal #предупреждение, если сравниваются вещественные числа
    -Wimplicit-fallthrough
    -Wunreachable-code #предупреждение, если код никогда не будет выполнен
    #-Werror
    -D_FILE_OFFSET_BITS=64
)

#add_executable(${PROJECT_NAME}
#    main.cpp
#    ssd1306_rpi_i2c.cpp
#    )

add_library(${PROJECT_NAME} STATIC
    #main.cpp
    ssd1306_rpi_i2c.cpp
    )

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${LIB_VERSION})
target_link_libraries(${PROJECT_NAME} pthread)


