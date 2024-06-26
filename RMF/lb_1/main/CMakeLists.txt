set(NAME robot_movement)
project(${NAME})

include_directories(include)

add_executable(${NAME})
target_sources(${NAME}
    PRIVATE
        main.cpp
        src/api/Bumper.cpp
        src/api/Com.cpp
        src/move/Square.cpp
)

if(MSVC) # Suppress MSVC warnings
    target_compile_definitions (${NAME} PUBLIC _CRT_SECURE_NO_WARNINGS )
endif(MSVC)

if(NOT DEFINED ROBOTINOAPI2_DIR)
    if(DEFINED ENV{ROBOTINOAPI2_64_DIR})
        set(ROBOTINOAPI2_DIR $ENV{ROBOTINOAPI2_64_DIR})
    else()
        message(FATAL_ERROR "Environment variable ROBOTINOAPI2_64_DIR
            or ROBOTINOAPI2_DIR variable is not defined.")
    endif()
endif()

set(CMAKE_MODULE_PATH "${ROBOTINOAPI2_DIR}\\cmake")
find_package(RobotinoAPI2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC ${REC_ROBOTINO_API2_LIBRARY})
target_include_directories(${PROJECT_NAME} INTERFACE ${ROBOTINOAPI2_INCLUDE_DIR})