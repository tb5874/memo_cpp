################################################################################
# Source
################################################################################
add_subdirectory(lib_make)
add_subdirectory(lib_use)

################################################################################
# Readme
################################################################################

# https://github.com/kaldi-asr/kaldi
# https://github.com/kaldi-asr/kaldi/blob/master/INSTALL
	# git clone https://github.com/kaldi-asr/kaldi.git
	# https://github.com/kaldi-asr/kaldi/blob/master/tools/INSTALL
		# cd kaldi/tools
		# ./extras/check_dependencies.sh
			# message check
			# " ./extras/check_dependencies.sh: all OK. "
		# make -j 8
	# https://github.com/kaldi-asr/kaldi/blob/master/src/INSTALL
		# cd kaldi/src
		# ./configure --shared
			# intel-oneMKL or OpenBLAS
			# cd /etc/ld.so.conf.d
				# sudo vi mkl_test.conf
					# /opt/intel/oneapi/mkl/latest/lib/pkgconfig/../../lib/intel64
			# message check
			# " Successfully configured for Linux with MKL libraries found in /opt/intel/mkl
			#   INFO: Configuring Kaldi not to link with Speex. Don't worry, it's only needed if you intend to use 'compress-uncompress-speex', which is very unlikely.
			#   Kaldi has been successfully configured. To compile: "
		# make depend -j 8
		# make -j 8

# CMakeLists.txt
	# target_include_directories()
		# "/home/user/ ### git clone path ### /kaldi/src"
		# "/home/user/ ### git clone path ### /kaldi/tools/openfst-1.7.2/src/include"
			# for below include ...
			# #include <feat/feature-fbank.h>
			# #include <base/kaldi-math.h>
			# #include <matrix/kaldi-matrix-inl.h>
			# #include <feat/wave-reader.h>
			# #include <fst/types.h>
	# target_link_directories()
		# "/home/user/ ### git clone path ### /kaldi/src/lib"
		# "/home/user/ ### git clone path ### /kaldi/tools/openfst-1.7.2/lib"
	# target_link_libraries()
		# "kaldi-base"
		# "kaldi-feat"
		# "kaldi-matrix"
		# "fst"

# For Binary Build Result !!! : -->
# Binary Build Result don't know, where kaldi library ...
# So, system need to know kaldi library path
	# cd /etc/ld.so.conf.d
		# sudo vi kaldi_test.conf
			# /home/user/ ### git clone path ### /kaldi/src/lib
			# /home/user/ ### git clone path ### /kaldi/tools/openfst-1.7.2/lib
		# sudo ldconfig
# Or you can copy kaldi library to Binary Build Result path.	
    # file(COPY "/home/user/ ### git clone path ### /kaldi/src/lib/libkaldi-chain.so" DESTINATION "${CMAKE_BINARY_DIR}")
	# file(COPY "/home/user/ ### git clone path ### /kaldi/src/lib/ ### .so" DESTINATION "${CMAKE_BINARY_DIR}")
	# ...
# For Binary Build Result !!! : <--
