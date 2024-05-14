set(PROJECT_NAME doyouknow_float_std)
set(ROOT_NAMESPACE doyouknow_float_std)
message(STATUS "PROJECT_NAME : [${PROJECT_NAME}]")
message(STATUS "ROOT_NAMESPACE : [${ROOT_NAMESPACE}]")


################################################################################
# Language CXX
################################################################################
if(True)

    enable_language(CXX)

    set(CMAKE_CXX_STANDARD_FORCE True)
    if (CMAKE_CXX_STANDARD_FORCE)
        set(CMAKE_CXX_STANDARD 17)
    endif()
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    ################################################################################
    # Language CXX Flag
    ################################################################################

    if(WIN32)
        # /ZI /Z7 -> /Zi
        # The /Zi option produces a separate PDB file that contains all the symbolic debugging information for use with the debugger.
        # The debugging information isn't included in the object files or executable, which makes them much smaller.
        # https://learn.microsoft.com/en-us/cpp/build/reference/z7-zi-zi-debug-information-format?view=msvc-170
        string(REGEX REPLACE "/Z[iI7]" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    endif()

    if(UNIX)
        # O1 O2 O3 -> O0
        # Optimize Level set 0
        # https://gcc.gnu.org/onlinedocs/gcc-11.4.0/gcc/Optimize-Options.html#index-O0
        string(REGEX REPLACE "-O[0123]" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        string(REGEX REPLACE "-O[0123]" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
        set(CMAKE_CXX_FLAGS_DEBUG "-O0 ${CMAKE_CXX_FLAGS_DEBUG}")
        set(CMAKE_CXX_FLAGS_RELEASE "-O0 ${CMAKE_CXX_FLAGS_RELEASE}")
    endif()

    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_COMPILER set to [${CMAKE_CXX_COMPILER}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_STANDARD_FORCE set to [${CMAKE_CXX_STANDARD_FORCE}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_STANDARD set to [${CMAKE_CXX_STANDARD}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_STANDARD_REQUIRED set to [${CMAKE_CXX_STANDARD_REQUIRED}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_FLAGS_DEBUG set to [${CMAKE_CXX_FLAGS_DEBUG}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_FLAGS_RELEASE set to [${CMAKE_CXX_FLAGS_RELEASE}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_BINARY_DIR set to [${CMAKE_BINARY_DIR}]")

endif()


################################################################################
# File list
################################################################################

# [ Type 1 ]
# The GLOB_RECURSE mode will traverse all the subdirectories of the matched directory and match the files.
file(GLOB_RECURSE cpp_file "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
source_group("cpp_file" FILES ${cpp_file})
file(GLOB_RECURSE hpp_file "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
source_group("hpp_file" FILES ${hpp_file})

# [ Type 2 ]
#set(cpp_file
#    "./###.cpp"
#    "./###.hpp"
#)

set(all_file ${cu_file} ${cuh_file} ${cpp_file} ${hpp_file})
message(STATUS "${PROJECT_NAME} : all_file set to [${all_file}]")


################################################################################
# Executable or Library
################################################################################
#add_executable(${PROJECT_NAME} ${all_file})
add_library(${PROJECT_NAME} SHARED ${all_file})


################################################################################
# User define flag
################################################################################
list(APPEND USER_DEFINE_FLAG
    # add flag
    EXPORT_FLAG
)
target_compile_definitions(${PROJECT_NAME} PRIVATE "${USER_DEFINE_FLAG}")
message(STATUS "${PROJECT_NAME} : USER_DEFINE_FLAG set to [${USER_DEFINE_FLAG}]")


################################################################################
# target_compile_options
################################################################################
if(WIN32)

    # CXX
    if(True)
        list(APPEND COMPILE_OPTIONS
            "$<$<COMPILE_LANGUAGE:CXX>:"
                "$<$<CONFIG:Debug>:"
                    # add flag
                    "/std:c++17" # Tells the compiler to conform to a specific language standard.
                    "/debug:all" # Generates complete debugging information.
                    "/Zi" # the compiler to generate symbolic debugging information in a program database (PDB) file for use with the debugger.
                    "/Od" # Disables all optimizations.
                    "/MDd" # Tells the linker to search for unresolved references in a multithreaded, dynamic-link runtime library. ( Debug )
                    # https://learn.microsoft.com/en-us/cpp/build/reference/fp-specify-floating-point-behavior?view=msvc-160
                    "/fp:precise"
                ">"
                "$<$<CONFIG:Release>:"
                    # add flag
                    "/MD" # Tells the linker to search for unresolved references in a multithreaded, dynamic-link runtime library. ( Release )
                ">"
                # add flag
                "/EHa" # Specifies the model of exception handling to be performed.
                "/Wall" # Enables warning and error diagnostics.
            ">"
        )
    endif()

elseif(UNIX)

    # CXX
    if(True)
        list(APPEND COMPILE_OPTIONS
            "$<$<COMPILE_LANGUAGE:CXX>:"
                "$<$<CONFIG:Debug>:"
                    # add flag
                    "-std=c++17" # Tells the compiler to conform to a specific language standard.
                    "-g" # Produce debugging information in the operating system¡¯s native format
                    "-O0" # Reduce compilation time and make debugging produce the expected results. This is the default.
                ">"
                "$<$<CONFIG:Release>:"
                    # add flag
                ">"
                # add flag
                "-Wall"
            ">"
        )
    endif()

endif()
target_compile_options(${PROJECT_NAME} PRIVATE "${COMPILE_OPTIONS}")
message(STATUS "${PROJECT_NAME} : COMPILE_OPTIONS set to [${COMPILE_OPTIONS}]")


################################################################################
# target_link_options
################################################################################
if(WIN32)

    # CXX
    if(True)
        list(APPEND LINK_OPTIONS
            "$<$<COMPILE_LANGUAGE:CXX>:"
                "$<$<CONFIG:Debug>:"
                    # add flag
                ">"
                "$<$<CONFIG:Release>:"
                    # add flag
                ">"
                # add flag
            ">"
        )
    endif()

elseif(UNIX)

    # CXX
    if(True)
        list(APPEND LINK_OPTIONS
            "$<$<COMPILE_LANGUAGE:CXX>:"
                "$<$<CONFIG:Debug>:"
                    # add flag                
                ">"
                "$<$<CONFIG:Release>:"
                    # add flag
                ">"
                # add flag
            ">"
        )
    endif()

endif()
target_link_options(${PROJECT_NAME} PRIVATE "${LINK_OPTIONS}")
message(STATUS "${PROJECT_NAME} : LINK_OPTIONS set to [${LINK_OPTIONS}]")


################################################################################
# target_include_directories() for use #include <~.h> 
################################################################################
if(WIN32)

    # CXX
    if(True)
        list(APPEND ADDITIONAL_INCLUDE_DIRECTORIES
            "$<$<CONFIG:Debug>:"
                # add directory path            
            ">"
            "$<$<CONFIG:Release>:"
                # add directory path
            ">"
            # add directory path
        )
    endif()

    # Common
    if(True)
        list(APPEND ADDITIONAL_INCLUDE_DIRECTORIES
            "$<$<CONFIG:Debug>:"
                # add directory path            
            ">"
            "$<$<CONFIG:Release>:"
                # add directory path
            ">"
            # add directory path
            "${CMAKE_CURRENT_SOURCE_DIR}"
        )
    endif()

elseif(UNIX)

    # CXX
    if(True)
        list(APPEND ADDITIONAL_INCLUDE_DIRECTORIES
            "$<$<CONFIG:Debug>:"
                # add directory path            
            ">"
            "$<$<CONFIG:Release>:"
                # add directory path
            ">"
            # add directory path
        )
    endif()

    # Common
    if(True)
        list(APPEND ADDITIONAL_INCLUDE_DIRECTORIES
            "$<$<CONFIG:Debug>:"
                # add directory path            
            ">"
            "$<$<CONFIG:Release>:"
                # add directory path
            ">"
            # add directory path
            "${CMAKE_CURRENT_SOURCE_DIR}"
        )
    endif()

endif()
target_include_directories(${PROJECT_NAME} PRIVATE "${ADDITIONAL_INCLUDE_DIRECTORIES}")
message(STATUS "${PROJECT_NAME} : ADDITIONAL_INCLUDE_DIRECTORIES set to [${ADDITIONAL_INCLUDE_DIRECTORIES}]")


################################################################################
# target_link_directories() for include ~.lib file.
################################################################################
if(WIN32)

    # CXX
    if(True)
        list(APPEND ADDITIONAL_LIBRARY_DIRECTORIES
            "$<$<CONFIG:Debug>:"
                # add directory path            
            ">"
            "$<$<CONFIG:Release>:"
                # add directory path
            ">"
            # add directory path
        )
    endif()

elseif(UNIX)

    # CXX
    if(True)
        list(APPEND ADDITIONAL_LIBRARY_DIRECTORIES
            "$<$<CONFIG:Debug>:"
                # add directory path            
            ">"
            "$<$<CONFIG:Release>:"
                # add directory path
            ">"
            # add directory path
        )
    endif()

endif()
target_link_directories(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DIRECTORIES}")
message(STATUS "${PROJECT_NAME} : ADDITIONAL_LIBRARY_DIRECTORIES set to [${ADDITIONAL_LIBRARY_DIRECTORIES}]")


################################################################################
# target_link_libraries() for use inside ~.lib function.
################################################################################
if(WIN32)

    # CXX
    if(True)
        list(APPEND ADDITIONAL_LIBRARY_LINK
            "$<$<CONFIG:Debug>:"
                # add library
            ">"
            "$<$<CONFIG:Release>:"
                # add library
            ">"
            # add library
        )
    endif()

elseif(UNIX)

    # CXX
    if(True)
        list(APPEND ADDITIONAL_LIBRARY_LINK
            "$<$<CONFIG:Debug>:"
                # add library
            ">"
            "$<$<CONFIG:Release>:"
                # add library
            ">"
            # add library
        )
    endif()

endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_LINK}")
message(STATUS "${PROJECT_NAME} : ADDITIONAL_LIBRARY_LINK set to [${ADDITIONAL_LIBRARY_LINK}]")

################################################################################
# Additional setting
################################################################################
#set(### "#####")
#add_dependencies(${PROJECT_NAME} "${###}")
#etc...

set(CMAKE_SHARED_LIBRARY_PREFIX "")

################################################################################
# Post build - copy
################################################################################
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # command format
    # add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/###.hpp" "${CMAKE_SOURCE_DIR}/out/Debug/###.hpp")
    # add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/###.hpp" "${CMAKE_SOURCE_DIR}/out/Release/###.hpp")
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/doyouknow_float_std.hpp" DESTINATION "${CMAKE_SOURCE_DIR}/out/Debug")    
else()
    # command format
    # add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/###.hpp" "${CMAKE_SOURCE_DIR}/out/Debug/###.hpp")
    # add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/###.hpp" "${CMAKE_SOURCE_DIR}/out/Release/###.hpp")
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/doyouknow_float_std.hpp" DESTINATION "${CMAKE_SOURCE_DIR}/out/Release")
endif()
message(STATUS "${PROJECT_NAME} : CMAKE_CURRENT_SOURCE_DIR set to [${CMAKE_CURRENT_SOURCE_DIR}]")
message(STATUS "${PROJECT_NAME} : CMAKE_SOURCE_DIR set to [${CMAKE_SOURCE_DIR}]")
