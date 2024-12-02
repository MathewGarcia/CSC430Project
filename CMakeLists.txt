cmake_minimum_required(VERSION 3.15)
project(CSC430Project)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)

add_definitions(-D_MBCS)

# Include libcurl directories
find_package(CURL REQUIRED) # Automatically finds libcurl if installed
include_directories(${CURL_INCLUDE_DIRS})

# Add executable target
add_executable(CSC430Project WIN32
    Bot.cpp
    Cancel.cpp
    Command.cpp
    CSC430Project.cpp
    DatabaseManager.cpp
    FindFile.cpp
    Help.cpp
    MessageHolder.cpp
    UserManager.cpp
)

# Link the necessary libraries
target_link_libraries(CSC430Project ${CURL_LIBRARIES})

target_link_options(CSC430Project PRIVATE /SUBSYSTEM:WINDOWS)
