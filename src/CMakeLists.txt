################################################################################
# Source
################################################################################
#add_subdirectory(doyouknow_bitfield)
#add_subdirectory(doyouknow_bitwise)
#add_subdirectory(doyouknow_class)
#add_subdirectory(doyouknow_fft)
add_subdirectory(doyouknow_float)
#add_subdirectory(doyouknow_function)
if(UNIX)
	add_subdirectory(doyouknow_kaldi)
endif()
#add_subdirectory(doyouknow_macro)
#add_subdirectory(doyouknow_ptr)
#add_subdirectory(doyouknow_vector)
add_subdirectory(doyouknow_wav)
