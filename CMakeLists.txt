cmake_minimum_required(VERSION 3.15)
project(CSC430Project)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)

add_definitions(-D_MBCS)

# Include MySQL Connector directories recursively
set(MYSQL_BASE_DIR "C:/Program Files/mysql-connector-c++-9.1.0-winx64/include")
include_directories(${MYSQL_BASE_DIR})
include_directories(${MYSQL_BASE_DIR}/jdbc)

# Link MySQL Connector libraries
set(MYSQL_LIB_DIR "C:/Program Files/mysql-connector-c++-9.1.0-winx64/lib64")
link_directories(${MYSQL_LIB_DIR})
link_directories(${MYSQL_LIB_DIR}/vs14)

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
    SignupWindow.cpp 
    SignupWindow.h ) 

# Link the necessary libraries
target_link_libraries(CSC430Project mysqlcppconn)

target_link_options(CSC430Project PRIVATE /SUBSYSTEM:WINDOWS)
