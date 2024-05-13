cmake_minimum_required(VERSION 3.9)

if(WIN32)
    #
elseif(UNIX)
    #
endif()
message(STATUS "Before project()")

################################################################################
# Start project()
################################################################################
project("doyouknow_cpp" LANGUAGES NONE)
message(STATUS "${PROJECT_NAME} : project() set to [${PROJECT_NAME}]")

################################################################################
# CMake Directory
################################################################################
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/out/Debug")
else()
    set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/out/Release")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

message(STATUS "${PROJECT_NAME} : CMAKE_BUILD_TYPE set to [${CMAKE_BUILD_TYPE}]") # source build type
message(STATUS "${PROJECT_NAME} : CMAKE_SOURCE_DIR set to [${CMAKE_SOURCE_DIR}]") # source directory path
message(STATUS "${PROJECT_NAME} : CMAKE_BINARY_DIR set to [${CMAKE_BINARY_DIR}]") # build output directory path
message(STATUS "${PROJECT_NAME} : CMAKE_ARCHIVE_OUTPUT_DIRECTORY set to [${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}]") # build output directory path
message(STATUS "${PROJECT_NAME} : CMAKE_LIBRARY_OUTPUT_DIRECTORY set to [${CMAKE_LIBRARY_OUTPUT_DIRECTORY}]") # build output directory path
message(STATUS "${PROJECT_NAME} : CMAKE_RUNTIME_OUTPUT_DIRECTORY set to [${CMAKE_RUNTIME_OUTPUT_DIRECTORY}]") # build output directory path

################################################################################
# Copy
################################################################################
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    #file(COPY "C:/#####/#####.dll" DESTINATION ${CMAKE_BINARY_DIR})
else()
    #file(COPY "C:/#####/#####.dll" DESTINATION ${CMAKE_BINARY_DIR})
endif()


################################################################################
# Source
################################################################################
add_subdirectory(src)
