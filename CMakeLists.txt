cmake_minimum_required(VERSION 3.20)

# Project name
project(Aggregate VERSION 0.1.0
        DESCRIPTION "Aggregate test task"
        HOMEPAGE_URL "https://github.com/S0ulM1ke"
        LANGUAGES CXX)


# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")


if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

# Add source files
set(PROJECT_SOURCES
    "${CMAKE_SOURCE_DIR}/main.cpp"
)

# Add include directories
include_directories(include)

# Create executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Add any required libraries (if needed)
# target_link_libraries(${PROJECT_NAME} <library_name>)