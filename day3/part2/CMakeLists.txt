project(day3_part2)

add_executable(${PROJECT_NAME}
        part2.cpp
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        utils
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

add_dependencies(${PROJECT_NAME} copy-resources)
