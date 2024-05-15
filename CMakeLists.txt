cmake_minimum_required(VERSION 3.9)

################################################################################

# tool -> option -> platform -> connect admin -> add
    # ip, port, linux username, linux userpassword

# CMakeSettings.json
# {
#   "configurations": [
#     {
#       "name": "Debug-Local-Windows-cl",
#       "generator": "Ninja",
#       "configurationType": "Debug",
#       "inheritEnvironments": [ "msvc_x64_x64" ],
#       "buildRoot": "${projectDir}\\out\\Debug\\build",
#       "installRoot": "${projectDir}\\out\\Debug\\install",
#       "cmakeCommandArgs": "",
#       "ctestCommandArgs": "",
#       "buildCommandArgs": "-v"
#     },
#     {
#       "name": "Release-Local-Windows-cl",
#       "generator": "Ninja",
#       "configurationType": "Release",
#       "buildRoot": "${projectDir}\\out\\Release\\build",
#       "installRoot": "${projectDir}\\out\\Release\\install",
#       "inheritEnvironments": [ "msvc_x64_x64" ],
#       "cmakeCommandArgs": "",
#       "ctestCommandArgs": "",
#       "buildCommandArgs": "-v"
#     },
#     {
#       "name": "Debug-Remote-Linux-gcc-tb",
#       "generator": "Unix Makefiles",
#       "configurationType": "Debug",
#       "cmakeExecutable": "cmake",
#       "remoteCopySourcesExclusionList": [ ".vs", ".git", "out" ],
#       //"cmakeCommandArgs": "-DCMAKE_CUDA_COMPILER=/usr/local/cuda/bin/nvcc",
#       "ctestCommandArgs": "",
#       "buildCommandArgs": "-j -l 80",
#       "inheritEnvironments": [ "linux_c++_x64" ],
#       "remoteMachineName": "${defaultRemoteMachineName}",
#       "remoteCMakeListsRoot": "$HOME/.vs/${projectDirName}/${workspaceHash}/Debug/src",
#       "remoteBuildRoot": "$HOME/.vs/${projectDirName}/${workspaceHash}/out/Debug/build/${name}",
#       "remoteInstallRoot": "$HOME/.vs/${projectDirName}/${workspaceHash}/out/Debug/install/${name}",
#       "remoteCopySources": true,
#       "rsyncCommandArgs": "-t --delete --delete-excluded",
#       "remoteCopyBuildOutput": false,
#       "remoteCopySourcesMethod": "rsync",
#       "addressSanitizerEnabled": false
#     },
#     {
#       "name": "Release-Remote-Linux-gcc-tb",
#       "generator": "Unix Makefiles",
#       "configurationType": "Release",
#       "cmakeExecutable": "cmake",
#       "remoteCopySourcesExclusionList": [ ".vs", ".git", "out" ],
#       //"cmakeCommandArgs": "-DCMAKE_CUDA_COMPILER=/usr/local/cuda/bin/nvcc",
#       "ctestCommandArgs": "",
#       "buildCommandArgs": "-j -l 80",
#       "inheritEnvironments": [ "linux_c++_x64" ],
#       "remoteMachineName": "${defaultRemoteMachineName}",
#       "remoteCMakeListsRoot": "$HOME/.vs/${projectDirName}/${workspaceHash}/Release/src",
#       "remoteBuildRoot": "$HOME/.vs/${projectDirName}/${workspaceHash}/out/Release/build/${name}",
#       "remoteInstallRoot": "$HOME/.vs/${projectDirName}/${workspaceHash}/out/Release/install/${name}",
#       "remoteCopySources": true,
#       "rsyncCommandArgs": "-t --delete --delete-excluded",
#       "remoteCopyBuildOutput": false,
#       "remoteCopySourcesMethod": "rsync",
#       "addressSanitizerEnabled": false
#     }
#   ]
# }

# launch.vs.json
# {
#   "version": "0.2.1",
#   "defaults": {},
#   "configurations": [
#     {
#       "project": "CMakeLists.txt",
#       "projectTarget": "doyouknow_float_use",
#       "name": "Linux : Debug",
#       "type": "cppgdb",
#       "debuggerConfiguration": "gdb",
#       "MIMode": "gdb",
#       //"gdbpath": "/usr/local/cuda-11.8/bin/cuda-gdb",
#       "args": [],
#       "env": {},
#       "setupCommands": [
#         //{
#         //  "description": "mi async off",
#         //  "text": "-gdb-set mi-async off",
#         //  "ignoreFailures": true
#         //},
#         //{
#         //  "description": "disassembly flavor to intel",
#         //  "text": "-gdb-set disassembly-flavor intel",
#         //  "ignoreFailures": true
#         //}
#       ]
#     }
#   ]
# }

################################################################################


################################################################################
# Before project()
################################################################################
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
    #file(COPY "C:/#####/#####.dll" DESTINATION "${CMAKE_SOURCE_DIR}/out/Debug")
else()
    #file(COPY "C:/#####/#####.dll" DESTINATION "${CMAKE_SOURCE_DIR}/out/Release")
endif()


################################################################################
# Source
################################################################################
add_subdirectory(src)
