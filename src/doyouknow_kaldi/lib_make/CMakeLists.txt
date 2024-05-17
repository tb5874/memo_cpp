####################################################################################################################

 ##  ##   ######   ######   ####              ######    ####              ####    ######   ######   ##  ##   #####   
 ### ##   ##       ##       ## ##               ##     ##  ##            ##       ##         ##     ##  ##   ##  ##  
 ######   #####    #####    ##  ##              ##     ##  ##             ####    #####      ##     ##  ##   ##  ##  
 ######   ##       ##       ##  ##              ##     ##  ##                ##   ##         ##     ##  ##   #####   
 ## ###   ##       ##       ## ##               ##     ##  ##                ##   ##         ##     ##  ##   ##      
 ##  ##   ######   ######   ####                ##      ####              ####    ######     ##     ######   ##    

##### set(PROJECT_NAME #####)     #####
##### set(ROOT_NAMESPACE #####)   #####
##### set(LIB_BUILD True or False)#####
##### target_link_libraries()     #####
##### set(depend_project_list "") #####

####################################################################################################################

set(PROJECT_NAME libstandard_kaldi)
set(ROOT_NAMESPACE libstandard_kaldi)
message(STATUS "PROJECT_NAME set to : [${PROJECT_NAME}]")
message(STATUS "ROOT_NAMESPACE set to : [${ROOT_NAMESPACE}]")

set(LIB_BUILD True)
message(STATUS "LIB_BUILD set to : [${LIB_BUILD}]")

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
        string(REGEX REPLACE "/Z[iI7]" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        string(REGEX REPLACE "/Z[iI7]" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG}")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    endif()

    if(UNIX)
        string(REGEX REPLACE "-O[0123]" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        string(REGEX REPLACE "-O[0123]" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    endif()

    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_COMPILER set to [${CMAKE_CXX_COMPILER}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_STANDARD_FORCE set to [${CMAKE_CXX_STANDARD_FORCE}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_STANDARD set to [${CMAKE_CXX_STANDARD}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_STANDARD_REQUIRED set to [${CMAKE_CXX_STANDARD_REQUIRED}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_FLAGS_DEBUG set to [${CMAKE_CXX_FLAGS_DEBUG}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_FLAGS_RELEASE set to [${CMAKE_CXX_FLAGS_RELEASE}]")

endif()


################################################################################
# File list
################################################################################

# [ Type 1 ]
# The GLOB_RECURSE mode will traverse all the subdirectories of the matched directory and match the files.
file(GLOB_RECURSE cpp_file "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE hpp_file "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

# [ Type 2 ]
#set(cpp_file
#    "./###.cpp"
#    "./###.hpp"
#)

set(all_file ${cpp_file} ${hpp_file})
message(STATUS "${PROJECT_NAME} : all_file set to [${all_file}]")


################################################################################
# Executable or Library
################################################################################
if(LIB_BUILD)
    add_library(${PROJECT_NAME} SHARED ${all_file})
else()
    add_executable(${PROJECT_NAME} ${all_file})
endif()


################################################################################
# User define flag
################################################################################
set(USER_DEFINE_FLAG "")
if(LIB_BUILD)
    list(APPEND USER_DEFINE_FLAG
        # add flag
        EXPORT_FLAG
    )
else()
    list(APPEND USER_DEFINE_FLAG
        # add flag
    )
endif()
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
                    "/Zi"
                        # https://learn.microsoft.com/en-us/cpp/build/reference/z7-zi-zi-debug-information-format?view=msvc-170
                        # The /Zi option produces a separate PDB file that contains all the symbolic debugging information for use with the debugger.
                        # The debugging information isn't included in the object files or executable, which makes them much smaller.
                    "/Od" # Disables all optimizations.
                ">"
                "$<$<CONFIG:Release>:"
                    # add flag
                ">"
                # add flag
                "/EHa" # Specifies the model of exception handling to be performed.
                "/Wall" # Enables warning and error diagnostics.
                "/fp:precise"
                    # https://learn.microsoft.com/en-us/cpp/build/reference/fp-specify-floating-point-behavior?view=msvc-160
                    # [ NaN, +infinity, -infinity, -0.0 ] are processed according to IEEE-754
                    # if x is NaN, [ x != x ] evaluates to true
            ">"
        )

        if(LIB_BUILD)
            list(APPEND COMPILE_OPTIONS
                "$<$<COMPILE_LANGUAGE:CXX>:"
                    "$<$<CONFIG:Debug>:"
                        "/MDd"
                            # https://learn.microsoft.com/en-us/cpp/build/reference/md-mt-ld-use-run-time-library?view=msvc-160
                            # create dynamic linking library ( Debug )
                    ">"
                    "$<$<CONFIG:Release>:"
                        "/MD"
                            # https://learn.microsoft.com/en-us/cpp/build/reference/md-mt-ld-use-run-time-library?view=msvc-160
                            # create dynamic linking library ( Release )
                    ">"
                ">"
            )
        endif()

    endif()

elseif(UNIX)

    # CXX
    if(True)
        list(APPEND COMPILE_OPTIONS
            "$<$<COMPILE_LANGUAGE:CXX>:"
                "$<$<CONFIG:Debug>:"
                    # add flag
                    "-std=c++17" # Tells the compiler to conform to a specific language standard.
                    "-g" # Produce debugging information in the operating system native format
                    "-O0"
                        # https://gcc.gnu.org/onlinedocs/gcc-11.4.0/gcc/Optimize-Options.html#index-O0
                        # Optimize Level set 0
                        # Reduce compilation time and make debugging produce the expected results. This is the default.
                ">"
                "$<$<CONFIG:Release>:"
                    # add flag
                ">"
                # add flag
                "-Wall"
                "-frounding-math"
                    # https://gcc.gnu.org/wiki/FloatingPointMath
                    # infinities, NaNs, gradual underflow, signed zeros, exception flags and traps, setting rounding modes.
                    # Compare with C99's #pragma STDC FENV ACCESS ON.
                    # Warning! GCC currently assumes that the same rounding mode is in effect everywhere (PR34678).
                    # use #include <cfenv>
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
                    "/DEBUG:FULL"
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
# target_include_directories() : for use #include <~.hpp> 
################################################################################
if(WIN32)

    # CXX
    if(True)
        list(APPEND ADDITIONAL_INCLUDE_DIRECTORIES
            "$<$<CONFIG:Debug>:"
                # add directory path
                "${CMAKE_SOURCE_DIR}/out/Debug"
            ">"
            "$<$<CONFIG:Release>:"
                # add directory path
                "${CMAKE_SOURCE_DIR}/out/Release"
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
                "${CMAKE_SOURCE_DIR}/out/Debug"
            ">"
            "$<$<CONFIG:Release>:"
                # add directory path
                "${CMAKE_SOURCE_DIR}/out/Release"
            ">"
            # add directory path
            "${CMAKE_CURRENT_SOURCE_DIR}"
            "/home/user/test_kaldi/kaldi/src"
            "/home/user/test_kaldi/kaldi/tools/openfst-1.7.2/src/include"
        )
    endif()

endif()
target_include_directories(${PROJECT_NAME} PRIVATE "${ADDITIONAL_INCLUDE_DIRECTORIES}")
message(STATUS "${PROJECT_NAME} : ADDITIONAL_INCLUDE_DIRECTORIES set to [${ADDITIONAL_INCLUDE_DIRECTORIES}]")


################################################################################
# target_link_directories() : for know where is external library file (~.so, ~.dll)
################################################################################
if(WIN32)

    # CXX
    if(True)
        list(APPEND ADDITIONAL_LIBRARY_DIRECTORIES
            "$<$<CONFIG:Debug>:"
                # add directory path
                "${CMAKE_SOURCE_DIR}/out/Debug"                    
            ">"
            "$<$<CONFIG:Release>:"
                # add directory path
                "${CMAKE_SOURCE_DIR}/out/Release"
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
                "${CMAKE_SOURCE_DIR}/out/Debug"
            ">"
            "$<$<CONFIG:Release>:"
                # add directory path
                "${CMAKE_SOURCE_DIR}/out/Release"
            ">"
            # add directory path
            "/home/user/test_kaldi/kaldi/src/lib"
            "/home/user/test_kaldi/kaldi/tools/openfst-1.7.2/lib"
        )
    endif()

endif()
target_link_directories(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DIRECTORIES}")
message(STATUS "${PROJECT_NAME} : ADDITIONAL_LIBRARY_DIRECTORIES set to [${ADDITIONAL_LIBRARY_DIRECTORIES}]")


################################################################################
# target_link_libraries() : for use external library file's function (~.so, ~.dll)
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
            "kaldi-base"
            "kaldi-feat"
            "kaldi-matrix"
            "fst"
        )
    endif()

endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_LINK}")
message(STATUS "${PROJECT_NAME} : ADDITIONAL_LIBRARY_LINK set to [${ADDITIONAL_LIBRARY_LINK}]")


################################################################################
# Additional setting
################################################################################
if(LIB_BUILD)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
else()
    # set(depend_project_list "")
    # add_dependencies(${PROJECT_NAME} ${depend_project_list})
endif()


################################################################################
# Post build - copy
################################################################################
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/###.hpp" "${CMAKE_SOURCE_DIR}/out/Debug/###.hpp")    
    if(LIB_BUILD)
        file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.hpp" DESTINATION "${CMAKE_SOURCE_DIR}/out/Debug")
    endif()
else()
    # add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/###.hpp" "${CMAKE_SOURCE_DIR}/out/Release/###.hpp")
    if(LIB_BUILD)
        file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.hpp" DESTINATION "${CMAKE_SOURCE_DIR}/out/Release")
    endif()
endif()
message(STATUS "${PROJECT_NAME} : CMAKE_CURRENT_SOURCE_DIR set to [${CMAKE_CURRENT_SOURCE_DIR}]")
message(STATUS "${PROJECT_NAME} : CMAKE_SOURCE_DIR set to [${CMAKE_SOURCE_DIR}]")
