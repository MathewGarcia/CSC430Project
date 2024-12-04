cmake_minimum_required(VERSION 3.15)
project(CSC430Project)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)

# Define necessary preprocessor definitions
add_definitions(-DCURL_STATICLIB -DZLIB_STATIC -D_UNICODE -DUNICODE)

# Enable static runtime linking
if (MSVC)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

# Debugging: Confirm project setup
message(STATUS "Building ${PROJECT_NAME} for ${CMAKE_SYSTEM_NAME} with Visual Studio")

# Add executable project
add_executable(CSC430Project WIN32
    Bot.cpp
    Cancel.cpp
    Command.cpp
    CSC430Project.cpp
    DatabaseAPI.cpp
    DatabaseAPI.h
    FindFile.cpp
    Help.cpp
    MessageHolder.cpp
    UserManager.cpp
    StartWindow.cpp
    StartWindow.h
    SignupWindow.cpp
    SignupWindow.h
)

# Include directories for CURL, OpenSSL, and Zlib
target_include_directories(CSC430Project PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/curl/include
    ${CMAKE_SOURCE_DIR}/third_party/openssl/include
    ${CMAKE_SOURCE_DIR}/third_party/zlib/include
)

# Link directories for CURL, OpenSSL, and Zlib
target_link_directories(CSC430Project PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/curl/lib
    ${CMAKE_SOURCE_DIR}/third_party/openssl/lib/VC/x64/MD
    ${CMAKE_SOURCE_DIR}/third_party/zlib/lib
)

# Link libraries for CURL, OpenSSL, Zlib (static), Winsock, and LDAP
target_link_libraries(CSC430Project PRIVATE
    libcurl.lib
    libcrypto.lib
    libssl.lib
    zlibstatic.lib  # Static Zlib
    ws2_32.lib      # Winsock
    wldap32.lib     # LDAP
)

# Set linker options to specify Windows subsystem
target_link_options(CSC430Project PRIVATE /SUBSYSTEM:WINDOWS)

# Debugging: Show all libraries and paths being used
message(STATUS "CURL include path: ${CMAKE_SOURCE_DIR}/third_party/curl/include")
message(STATUS "CURL library path: ${CMAKE_SOURCE_DIR}/third_party/curl/lib")
message(STATUS "OpenSSL include path: ${CMAKE_SOURCE_DIR}/third_party/openssl/include")
message(STATUS "OpenSSL library path: ${CMAKE_SOURCE_DIR}/third_party/openssl/lib/VC/x64/MD")
message(STATUS "Zlib include path: ${CMAKE_SOURCE_DIR}/third_party/zlib/include")
message(STATUS "Zlib library path: ${CMAKE_SOURCE_DIR}/third_party/zlib/lib")
message(STATUS "Linking libraries: libcurl.lib, libcrypto.lib, libssl.lib, zlibstatic.lib, ws2_32.lib, wldap32.lib")
