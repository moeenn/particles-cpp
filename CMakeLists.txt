cmake_minimum_required(VERSION 3.10)
project(particles VERSION 1.0.0 LANGUAGES CXX)

# generate the compile_commands.json file.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
if (PROJECT_IS_TOP_LEVEL AND UNIX)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "include" "vendor/SFML-3.0.0/include")
target_link_directories(${PROJECT_NAME} PRIVATE "vendor/SFML-3.0.0/lib")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_compile_options(${PROJECT_NAME} PUBLIC -Wextra -Werror -Wall -Wpedantic)
target_link_libraries(${PROJECT_NAME} m sfml-graphics sfml-window sfml-system) 
