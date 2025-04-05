project(day2_part1)

add_executable(${PROJECT_NAME}
        part1.cpp
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        utils
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

add_dependencies(${PROJECT_NAME} copy-resources)
