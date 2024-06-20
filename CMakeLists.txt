cmake_minimum_required(VERSION 2.8.5...3.27.5)
project(MazeTrix)

# Debug mode
set(FLAGS "-Wall -Wextra")
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

# CMake settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${FLAGS} -g3 -fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${FLAGS} -O3")

# =-=-=-=-=-=-= DOCS =-=-=-=-=-=-=
if (DOXYGEN_FOUND)
    message("Doxygen found. You can use `make docs`")

    add_custom_target(
        docs
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        VERBATIM
    )
else (DOXYGEN_FOUND)
    message("Doxygen not found. You won't be able to use `make docs`")
endif (DOXYGEN_FOUND)


# =-=-=-=-=-=-= EXECUTABLE =-=-=-=-=-=-=
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Source files
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(
    SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/cell.cpp
    ${SOURCE_DIR}/maze.cpp
    ${SOURCE_DIR}/pathfinder.cpp
    ${SOURCE_DIR}/race.cpp
    ${SOURCE_DIR}/random.cpp
    ${SOURCE_DIR}/structs.cpp
)

# Adding executables
add_executable(MazeTrix ${SOURCE_FILES})

# Libraries
target_link_directories(
    MazeTrix
    PRIVATE
    ${CMAKE_SOURCE_DIR}/raylib/lib
)
target_link_libraries(
    MazeTrix
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/raylib/lib/libraylib.so.5.0.0"
)

# Header files
target_include_directories(
    MazeTrix
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/raylib/include
)
