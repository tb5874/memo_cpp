################################################################################
# Project name
################################################################################
message(STATUS "${PROJECT_NAME} : PROJECT_NAME set to ${PROJECT_NAME}")

################################################################################
# Sub-projects
################################################################################
add_subdirectory(doyouknow_bitfield)
add_subdirectory(doyouknow_bitwise)
add_subdirectory(doyouknow_ptr)
add_subdirectory(doyouknow_vector)
