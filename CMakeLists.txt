cmake_minimum_required(VERSION 3.15)
project(RaytracingCPU)

set(CMAKE_CXX_STANDARD 20)

# dev
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# output

add_compile_definitions(PNG_OUTPUT_DIRECTORY="${CMAKE_SOURCE_DIR}/output/")

# dependencies

include_directories(third_party)

## stb
include_directories(third_party/stb)

## GLM
add_subdirectory(third_party/glm)

# source

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.h)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC glm)
