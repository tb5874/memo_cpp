#pragma once
#include <iostream>
#include <chrono>

class DOYOUKNOW_CLASS
{
	public:
		DOYOUKNOW_CLASS(void);
		~DOYOUKNOW_CLASS(void);

	public:
		void kaldi_fft(void);
		void fft_step01(float* xr, float* xi, int logn);
		void fft_step02(float* xr, float* xi, int logn);
		void fft_step03_04(float* xr, float* xi, int logn);
		void fft_unit(float* xr, float* xi, int logn);
		void fft_unit2(float* xr, float* xi, int logn);
		void fft_unit4(float* xr, float* xi, int logn);
		void fft_unit6(float* xr, float* xi, int logn);

};
