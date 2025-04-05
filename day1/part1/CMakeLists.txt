project(day1_part1)

#find_package(<package name> REQUIRED COMPONENTS <component 1> <component 2>)

add_executable(${PROJECT_NAME}
        part1.cpp
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        utils
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

add_dependencies(${PROJECT_NAME} copy-resources)
