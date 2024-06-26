#pragma once

#include <feat/feature-fbank.h>
#include <base/kaldi-math.h>
#include <matrix/kaldi-matrix-inl.h>
#include <feat/wave-reader.h>
#include <fst/types.h>

#include <string>
#include <exception>
#include <chrono>
#include <iostream>

class doyouknow_class{

	public:
		doyouknow_class(void);
		~doyouknow_class(void);

	public:
		void func_01(void);
		void func_02(void);

	public:
		void read_char8(std::istream& get_fs, int get_count);
		int read_int32(std::istream& get_fs);
		float read_fp32(std::istream& get_fs);

};
