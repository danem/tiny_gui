cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)

project(tiny_gui)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES 
    ${SOURCE_DIR}/font.cc
    ${SOURCE_DIR}/graphics.cc
    ${SOURCE_DIR}/layout.cc
    ${SOURCE_DIR}/linked_list.cc
    ${SOURCE_DIR}/widgets.cc
)

add_library(tiny_gui ${SOURCES})
target_include_directories(tiny_gui PUBLIC ${INCLUDE_DIR})

option(BUILD_EXAMPLES "Build examples. (They Use SimpleGL)" ON)
option(BUILD_TESTS "Build tests" ON)

if(BUILD_EXAMPLES)

    find_package(SimpleGL REQUIRED)
    find_package(SimpleGLHelpers REQUIRED)

    add_executable(draw_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/draw_test.cc)
    target_compile_definitions(draw_test PUBLIC -DSYNTH_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/tests/data")
    target_link_libraries(draw_test PRIVATE
        SimpleGL::SimpleGL 
        SimpleGLHelpers::SimpleGLHelpers 
        tiny_gui
    )

    add_executable(framebuffer_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/framebuffer_test.cc)
    target_link_libraries(framebuffer_test PRIVATE tiny_gui)

    add_executable(font_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/font_test.cc)
    target_compile_definitions(font_test PUBLIC -DSYNTH_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/tests/data")
    target_link_libraries(font_test PRIVATE
        SimpleGL::SimpleGL 
        SimpleGLHelpers::SimpleGLHelpers 
        tiny_gui
    )

    add_executable(widget_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/widget_test.cc)
    target_compile_definitions(widget_test PUBLIC -DSYNTH_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/tests/data")
    target_link_libraries(widget_test PRIVATE
        SimpleGL::SimpleGL 
        SimpleGLHelpers::SimpleGLHelpers 
        tiny_gui
    )

    add_executable(linked_list_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/linked_list_test.cc)
    target_link_libraries(linked_list_test PRIVATE tiny_gui)

endif()