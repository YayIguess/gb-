cmake_minimum_required(VERSION 3.15)
project(gb++)
set(CMAKE_CXX_STANDARD 17)
include(FindPkgConfig)

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)


include_directories(${GLFW_INCLUDE_DIRS} ${Vulkan_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp cpu.cpp opcode.cpp ppu.cpp vulkan.cpp)


target_compile_options(${PROJECT_NAME} PUBLIC
        -Wall
        -Wextra
        )

target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES} glfw)
