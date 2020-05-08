cmake_minimum_required(VERSION 3.15)
project(gb++)
set(CMAKE_CXX_STANDARD 17)
include(FindPkgConfig)

find_package(Vulkan REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories( ${GLFW_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${Vulkan_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp cpu.cpp opcode.cpp ppu_sdl.cpp ppu.h)


target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Ofast
        -I/usr/include/SDL2 -D_REENTRANT
        -L/usr/lib -pthread -lSDL2
        )
target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${Vulkan_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES} glfw ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
