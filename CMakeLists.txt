cmake_minimum_required (VERSION 3.10)
project(my-imtui-project)

enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS "on")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(cmake/GitVars.cmake)
include(cmake/BuildTypes.cmake)

if (MINGW)
    set(BUILD_SHARED_LIBS_DEFAULT OFF)
else()
    set(BUILD_SHARED_LIBS_DEFAULT ON)
endif()

# options

option(MY_IMTUI_PROJECT_ALL_WARNINGS            "Enable all compiler warnings" ON)
option(MY_IMTUI_PROJECT_ALL_WARNINGS_3RD_PARTY  "Enable all compiler warnings in 3rd party libs" OFF)

option(MY_IMTUI_PROJECT_SANITIZE_THREAD         "Enable thread sanitizer" OFF)
option(MY_IMTUI_PROJECT_SANITIZE_ADDRESS        "Enable address sanitizer" OFF)
option(MY_IMTUI_PROJECT_SANITIZE_UNDEFINED      "Enable undefined sanitizer" OFF)

# sanitizers

if (MY_IMTUI_PROJECT_SANITIZE_THREAD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=thread")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
endif()

if (MY_IMTUI_PROJECT_SANITIZE_ADDRESS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif()

if (MY_IMTUI_PROJECT_SANITIZE_UNDEFINED)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

# dependencies

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third-party)

# main

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
endif ()

add_subdirectory(src)
