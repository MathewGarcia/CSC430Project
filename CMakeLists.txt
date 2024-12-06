cmake_minimum_required(VERSION 3.15)

project(CSC430Project)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)

# Define the MySQL Connector directory
set(MYSQL_CONNECTOR_DIR "C:/Program Files/MySQL/MySQL Connector C++ 9.1")

# Define the MySQL Plugin directory
set(MYSQL_PLUGIN_DIR "${MYSQL_CONNECTOR_DIR}/lib64/plugin")

# Check if MySQL Connector is already installed
find_path(MYSQL_INCLUDE_DIR
    NAMES mysql_driver.h
    PATHS "${MYSQL_CONNECTOR_DIR}/include/jdbc"
    NO_DEFAULT_PATH
)

find_library(MYSQL_LIB
    NAMES mysqlcppconn
    PATHS "${MYSQL_CONNECTOR_DIR}/lib64/vs14"
    NO_DEFAULT_PATH
)

# Debug messages
message(STATUS "MySQL include directory: ${MYSQL_INCLUDE_DIR}")
message(STATUS "MySQL library: ${MYSQL_LIB}")
message(STATUS "MySQL plugin directory: ${MYSQL_PLUGIN_DIR}")

if (MYSQL_INCLUDE_DIR AND MYSQL_LIB)
    # Use pre-installed MySQL Connector
    message(STATUS "Using pre-installed MySQL Connector")
    include_directories("${MYSQL_INCLUDE_DIR}")
else()
    # MySQL Connector not found, download and set up paths
    message(STATUS "MySQL Connector not found, downloading and installing...")

    include(ExternalProject)
    ExternalProject_Add(mysql_connector
        URL https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-9.1.0-winx64.zip
        PREFIX "${CMAKE_BINARY_DIR}/mysql_connector"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
    )

    # Use paths for the downloaded MySQL Connector
    set(MYSQL_INCLUDE_DIR "${CMAKE_BINARY_DIR}/mysql_connector/src/mysql_connector/include")
    set(MYSQL_LIB "${CMAKE_BINARY_DIR}/mysql_connector/src/mysql_connector/lib64/mysqlcppconn.lib")
    include_directories("${MYSQL_INCLUDE_DIR}")
    include_directories("${MYSQL_INCLUDE_DIR}/jdbc")
endif()

# Add your executable
add_executable(CSC430Project
    Bot.cpp
    Command.cpp
    CSC430Project.cpp
    DatabaseManager.cpp
    FindFile.cpp
    MessageHolder.cpp
    UserManager.cpp
)

# Link libraries
target_link_libraries(CSC430Project "${MYSQL_LIB}")

# Set subsystem to Windows
target_link_options(CSC430Project PRIVATE /SUBSYSTEM:CONSOLE)

# Define the path to MySQL Connector and MySQL Server libraries
set(MYSQL_DLL_DIR "${MYSQL_CONNECTOR_DIR}/lib64")
set(MYSQL_SERVER_LIB_DIR "C:/Program Files/MySQL/MySQL Server 9.1/lib")

# Copy the MySQL Connector, OpenSSL, and plugin DLLs after build
add_custom_command(TARGET CSC430Project POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MYSQL_DLL_DIR}/mysqlcppconn-10-vs14.dll"
        "$<TARGET_FILE_DIR:CSC430Project>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MYSQL_DLL_DIR}/libcrypto-3-x64.dll"
        "$<TARGET_FILE_DIR:CSC430Project>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MYSQL_DLL_DIR}/libssl-3-x64.dll"
        "$<TARGET_FILE_DIR:CSC430Project>"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${MYSQL_PLUGIN_DIR}"
        "$<TARGET_FILE_DIR:CSC430Project>/lib64/plugin"
    COMMENT "Copying MySQL Connector, OpenSSL, and plugins to output directory"
)

# Install rules
install(TARGETS CSC430Project
    RUNTIME DESTINATION bin
)

install(FILES
    "${MYSQL_DLL_DIR}/mysqlcppconn-10-vs14.dll"
    "${MYSQL_DLL_DIR}/libcrypto-3-x64.dll"
    "${MYSQL_DLL_DIR}/libssl-3-x64.dll"
    DESTINATION bin
)

install(DIRECTORY
    "${MYSQL_PLUGIN_DIR}"
    DESTINATION bin
)

# Include CPack for packaging
set(CPACK_PACKAGE_NAME "CSC430Project")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_GENERATOR "ZIP") # Options: ZIP, NSIS, etc.

include(CPack)
