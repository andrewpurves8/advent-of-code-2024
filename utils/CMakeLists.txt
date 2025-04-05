project(utils)

set(INTERFACE_FILES
        include/FileReader.h
        include/InputConversions.h
        include/ProgramOptions.h
        include/Types.h
)

set(IMPLEMENTATION_SOURCES
        src/FileReader.cpp
        src/InputConversions.cpp
        src/ProgramOptions.cpp
)

add_library(${PROJECT_NAME} STATIC
        ${INTERFACE_FILES}
        ${IMPLEMENTATION_SOURCES}
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        include
)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY include DESTINATION .)