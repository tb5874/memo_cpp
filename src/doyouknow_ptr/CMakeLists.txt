set(PROJECT_NAME doyouknow_ptr)
set(ROOT_NAMESPACE doyouknow_ptr)

################################################################################
# required package
################################################################################
if(MSVC)
    #
elseif(UNIX)
    #
endif()

################################################################################
# Project name
################################################################################
message(STATUS "${PROJECT_NAME} : PROJECT_NAME set to ${PROJECT_NAME}")

################################################################################
# Source groups
################################################################################
set(src_doyouknow_ptr
    "doyouknow_ptr.cpp"
    "doyouknow_ptr.hpp"
)
source_group("src_bf16TensorCoreGemm" FILES ${src_doyouknow_ptr})
set(ALL_FILES
    ${src_doyouknow_ptr}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

################################################################################
# Include directories
################################################################################
if(MSVC)
    list(APPEND ADD_INCLUDE_DIRECTORY
        #
    )
elseif(UNIX)
    list(APPEND ADD_INCLUDE_DIRECTORY
        #
    )
endif()
list(APPEND ADD_INCLUDE_DIRECTORY
    #
)
target_include_directories(${PROJECT_NAME} PUBLIC "${ADD_INCLUDE_DIRECTORY}")
message(STATUS "${PROJECT_NAME} : ADD_INCLUDE_DIRECTORY set to ${ADD_INCLUDE_DIRECTORY}")

################################################################################
# Library path
################################################################################
 if (MSVC)
    list(APPEND ADD_LIBRARY_PATH
        #
    )
elseif(UNIX)
    list(APPEND ADD_LIBRARY_PATH
        #
    )
endif()
list(APPEND ADD_LIBRARY_PATH
    #
)
target_link_directories(${PROJECT_NAME} PUBLIC "${ADD_LIBRARY_PATH}")
message(STATUS "${PROJECT_NAME} : ADD_LIBRARY_PATH set to ${ADD_LIBRARY_PATH}")

################################################################################
# Library dependency
################################################################################
if(MSVC)
    list(APPEND ADD_LIBRARY_DEPENDENCY
        "$<$<CONFIG:Debug>:"
            #
        ">"
        "$<$<CONFIG:Release>:"
            #
        ">"
        #
    )
elseif(UNIX)
    list(APPEND ADD_LIBRARY_DEPENDENCY
        "$<$<CONFIG:Debug>:"
            #
        ">"
        "$<$<CONFIG:Release>:"
            #
        ">"
        #
    )
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADD_LIBRARY_DEPENDENCY}")
message(STATUS "${PROJECT_NAME} : ADD_LIBRARY_DEPENDENCY set to ${ADD_LIBRARY_DEPENDENCY}")

################################################################################
# Compile definitions
################################################################################
if(MSVC)
   list(APPEND COMPILE_DEF 
        "$<$<CONFIG:Debug>:"
            "_DEBUG" 
        ">"
        "$<$<CONFIG:Release>:"
            #
        ">"
        #
    )
elseif(UNIX)
    list(APPEND COMPILE_DEF
        "$<$<CONFIG:Debug>:"
            #
        ">"
        "$<$<CONFIG:Release>:"
            #
        ">"
        #
    )
endif()
target_compile_definitions(${PROJECT_NAME} PUBLIC "${COMPILE_DEF}")
message(STATUS "${PROJECT_NAME} : COMPILE_DEF set to ${COMPILE_DEF}")

################################################################################
# Compile options
################################################################################
if(MSVC)
    list(APPEND COMPILE_OPT
        "$<$<CONFIG:Debug>:"
            #
        ">"
        "$<$<CONFIG:Release>:"
            #
        ">"
        "$<$<COMPILE_LANGUAGE:CXX>:"
            #
        ">"
        #
   )
elseif(UNIX)
    list(APPEND COMPILE_OPT
        "$<$<CONFIG:Debug>:"
            #
        ">"
        "$<$<CONFIG:Release>:"
            #
        ">"
        #
    )
endif()
list(APPEND COMPILE_OPT
    "${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}"
    "${DEFAULT_CXX_EXCEPTION_HANDLING}"
)
target_compile_options(${PROJECT_NAME} PRIVATE "${COMPILE_OPT}")
message(STATUS "${PROJECT_NAME} : COMPILE_OPT set to ${COMPILE_OPT}")

################################################################################
# LInker options
################################################################################
if(MSVC)
    list(APPEND LINKER_OPT
        "$<$<CONFIG:Debug>:"
            #
        ">"
        "$<$<CONFIG:Release>:"
            "/OPT:REF"
            "/OPT:ICF"
        ">"
        "/DYNAMICBASE"
        "/NXCOMPAT"
    )
elseif(UNIX)
    list(APPEND LINKER_OPT
    )
endif()
target_link_options(${PROJECT_NAME} PRIVATE "${LINKER_OPT}")
message(STATUS "${PROJECT_NAME} : LINKER_OPT set to ${LINKER_OPT}")
