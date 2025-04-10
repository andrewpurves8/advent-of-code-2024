cmake_minimum_required(VERSION 3.14)

project(advent-of-code-2024)

set(CMAKE_CXX_STANDARD 17)
set(OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/bin)

add_custom_target(copy-resources
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/example_inputs
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/example_inputs ${CMAKE_BINARY_DIR}/example_inputs
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/inputs
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/inputs ${CMAKE_BINARY_DIR}/inputs
        COMMENT "Copying resources"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
add_custom_command(TARGET copy-resources
        POST_BUILD
        COMMAND echo "Executing a POST_BUILD command"
)

add_subdirectory(utils)
add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
add_subdirectory(day5)
