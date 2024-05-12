#include <doyouknow_fft.hpp>

DOYOUKNOW_CLASS::DOYOUKNOW_CLASS(void) {
	return;
}

DOYOUKNOW_CLASS::~DOYOUKNOW_CLASS(void) {
	return;
}

void DOYOUKNOW_CLASS::kaldi_fft(void) {
	try {

		// 512	(total)
		// 256	(even) | 256 (odd)
		// 256	(2^8)

		// 8	logn
		// 256	m
		// 128	m2
		// 64	m4
		// 32	m8

		int test_item = 0;
		int test_logn = 0;

		float* test_x = nullptr;
		float* test_xr = nullptr;
		float* test_xi = nullptr;

		test_item = 512;	// 2^9, 512
		test_logn = 8;		// 2^8, 256

		test_x = (float*)std::malloc(sizeof(float) * test_item);
		test_xr = test_x;
		test_xi = test_x + (test_item / 2);

		for (int idx = 0; idx < test_item / 2; idx++) {
			test_xr[idx] = 1.0f;
		}

		for (int idx = 0; idx < test_item / 2; idx++) {
			test_xi[idx] = 2.0f;
		}

		std::chrono::steady_clock::time_point chrono_tick = std::chrono::steady_clock::now();		
		// need to summary functions ... : <--

		// logn > 0
		fft_unit(test_xr, test_xi, test_logn);

		// logn > 2
		fft_unit2(test_xr, test_xi, test_logn);

		// logn > 4
		fft_unit4(test_xr, test_xi, test_logn);

		// logn > 6
		fft_unit6(test_xr, test_xi, test_logn);

		// logn > 8
		// fft_unit8(xr, xi, logn);

		// logn > 10
		// fft_unit10(xr, xi, logn);

		// ...

		// logn > N
		// fft_unitN(xr, xi, logn);

		// need to summary functions ... : -->
		std::chrono::duration<double>chrono_tok = std::chrono::steady_clock::now() - chrono_tick;

		printf("FFT time : %20.10f", chrono_tok);

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

void DOYOUKNOW_CLASS::fft_step01(float* xr, float* xi, int logn) {

	int logn_ = logn;
	int m = 1 << logn_;
	int m2 = 1 << (logn_ - 1);

	float* xr1 = xr;
	float* xr2 = xr + m2;
	float* xi1 = xi;
	float* xi2 = xi + m2;

	float result_xr1 = 0.0f;
	float result_xr2 = 0.0f;
	float result_xi1 = 0.0f;
	float result_xi2 = 0.0f;

	// Parallel programming : -->
	for (int idx = 0; idx < m2; idx++) {

		result_xr1 = *xr1 + *xr2;
		result_xr2 = *xr1 - *xr2;
		result_xi1 = *xi1 + *xi2;
		result_xi2 = *xi1 - *xi2;

		*xr1 = result_xr1;
		*xr2 = result_xr2;
		*xi1 = result_xi1;
		*xi2 = result_xi2;

		xr1++;
		xr2++;
		xi1++;
		xi2++;

	}
	// Parallel programming : <--

	return;

};

void DOYOUKNOW_CLASS::fft_step02(float* xr, float* xi, int logn) {

	if (logn > 1) {

		int logn_ = logn;
		int m = 1 << logn_;
		int m2 = 1 << (logn_ - 1);
		int m4 = 1 << (logn_ - 2);

		float* xr1 = xr + m2;
		float* xr2 = xr + m2 + m4;
		float* xi1 = xi + m2;
		float* xi2 = xi + m2 + m4;

		float result_xr1 = 0.0f;
		float result_xr2 = 0.0f;
		float result_xi1 = 0.0f;
		float result_xi2 = 0.0f;

		// Parallel programming : -->
		for (int idx = 0; idx < m4; idx++) {

			result_xr1 = *xr1 + *xi2;
			result_xr2 = *xr1 - *xi2;
			result_xi1 = *xi1 - *xr2;
			result_xi2 = *xi1 + *xr2;

			*xr1 = result_xr1;
			*xr2 = result_xr2;
			*xi1 = result_xi1;
			*xi2 = result_xi2;

			xr1++;
			xr2++;
			xi1++;
			xi2++;

		}
		// Parallel programming : <--

	}

	return;

}

void DOYOUKNOW_CLASS::fft_step03_04(float* xr, float* xi, int logn) {

	// if logn == 2
		// m4 always 1.

	// if m4 == 1
		// idx always 0.
		// So, math result always same.
			// input == output
			// you can logn <= 2 skip ...

	if (logn > 2) {

		int logn_ = logn;
		int m = 1 << logn_;
		int m2 = 1 << (logn_ - 1);
		int m4 = 1 << (logn_ - 2);

		float* xr1 = xr + m2;
		float* xr2 = xr + m2 + m4;
		float* xi1 = xi + m2;
		float* xi2 = xi + m2 + m4;

		float result_xr1 = 0.0f;
		float result_xr2 = 0.0f;
		float result_xi1 = 0.0f;
		float result_xi2 = 0.0f;

		// https://github.com/python/cpython/blob/main/Include/pymath.h
		// 3.14159265358979323846;
		// 6.28318530717958647692;
		float float_2pi = 6.28318530717958647692f;
		float ang = 0.0f;
		float c = 0.0f;
		float s = 0.0f;
		float cn = 0.0f;
		float spcn = 0.0f;
		float smcn = 0.0f;
		float c3n = 0.0f;
		float spc3n = 0.0f;
		float smc3n = 0.0f;


		// if you want include '++' to 'for statement',
		// comment below 4 line and modify 'idx = 0' : --> 
		xr1++;
		xr2++;
		xi1++;
		xi2++;
		// comment below 4 line and modify 'idx = 0' : <--


		// Parallel programming : -->
		for (int idx = 1; idx < m4; idx++) {

			ang = (float)(idx) / (float)m * float_2pi;
			c = std::cos(ang);
			s = std::sin(ang);
			cn = c;
			spcn = -(s + c);
			smcn = s - c;

			ang = 3.0f * (float)idx / (float)m * float_2pi;
			c = std::cos(ang);
			s = std::sin(ang);
			c3n = c;
			spc3n = -(s + c);
			smc3n = s - c;

			result_xr1 = cn * (*xr1 + *xi1) + smcn * (*xi1);
			result_xr2 = c3n * (*xr2 + *xi2) + smc3n * (*xi2);
			result_xi1 = cn * (*xr1 + *xi1) + spcn * (*xr1);
			result_xi2 = c3n * (*xr2 + *xi2) + spc3n * (*xr2);

			// if you don't care float point error,
			// comment below 7 line ( kaldi step 3 & 4 ) : -->
			if ((m4 != 1) && ((m4 / 2) == idx)) {
				float sqhalf = 1.0f / std::sqrt(2.0f);
				result_xr1 = sqhalf * (*xr1 + *xi1);
				result_xi1 = sqhalf * (*xi1 - *xr1);
				result_xr2 = sqhalf * (*xi2 - *xr2);
				result_xi2 = -sqhalf * (*xr2 + *xi2);
			}
			// comment below 7 line ( kaldi step 3 & 4 ) : <--

			*xr1 = result_xr1;
			*xr2 = result_xr2;
			*xi1 = result_xi1;
			*xi2 = result_xi2;

			xr1++;
			xr2++;
			xi1++;
			xi2++;

		}
		// Parallel programming : <--

	}

	return;

}

void DOYOUKNOW_CLASS::fft_unit(float* xr, float* xi, int logn) {
	try {

		for (int idx = logn; idx > 0; idx--) {
			fft_step01(xr, xi, idx);
			fft_step02(xr, xi, idx);
			fft_step03_04(xr, xi, idx);
		}

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

void DOYOUKNOW_CLASS::fft_unit2(float* xr, float* xi, int logn) {
	try {

		int logn_ = 0;
		int m = 0;
		int m2 = 0;
		int m4 = 0;
		float* xr_ptr = nullptr;
		float* xi_ptr = nullptr;

		for (int idx = logn; idx > 2; idx--) {

			//////////////////////////////////////////////////
			logn_ = idx;
			m = 1 << logn_;
			m2 = 1 << (logn_ - 1);
			m4 = 1 << (logn_ - 2);
			xr_ptr = xr;
			xi_ptr = xi;

			xr_ptr = xr_ptr + m2;
			xi_ptr = xi_ptr + m2;
			fft_unit(xr_ptr, xi_ptr, logn_ - 2);
			xr_ptr = xr_ptr + m4;
			xi_ptr = xi_ptr + m4;
			fft_unit(xr_ptr, xi_ptr, logn_ - 2);
			//////////////////////////////////////////////////

		}

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

void DOYOUKNOW_CLASS::fft_unit4(float* xr, float* xi, int logn) {
	try {

		int logn_ = 0;
		int m = 0;
		int m2 = 0;
		int m4 = 0;
		float* xr_ptr = nullptr;
		float* xi_ptr = nullptr;

		for (int idx = logn; idx > 4; idx--) {
			for (int div = idx - 2; div > 2; div--) {

				//////////////////////////////////////////////////
				logn_ = idx;
				m = 1 << logn_;
				m2 = 1 << (logn_ - 1);
				m4 = 1 << (logn_ - 2);
				xr_ptr = xr + m2;
				xi_ptr = xi + m2;

				logn_ = div;
				m = 1 << logn_;
				m2 = 1 << (logn_ - 1);
				m4 = 1 << (logn_ - 2);

				xr_ptr = xr_ptr + m2;
				xi_ptr = xi_ptr + m2;
				fft_unit(xr_ptr, xi_ptr, logn_ - 2);
				xr_ptr = xr_ptr + m4;
				xi_ptr = xi_ptr + m4;
				fft_unit(xr_ptr, xi_ptr, logn_ - 2);
				//////////////////////////////////////////////////
				logn_ = idx;
				m = 1 << logn_;
				m2 = 1 << (logn_ - 1);
				m4 = 1 << (logn_ - 2);
				xr_ptr = xr + m2 + m4;
				xi_ptr = xi + m2 + m4;

				logn_ = div;
				m = 1 << logn_;
				m2 = 1 << (logn_ - 1);
				m4 = 1 << (logn_ - 2);

				xr_ptr = xr_ptr + m2;
				xi_ptr = xi_ptr + m2;
				fft_unit(xr_ptr, xi_ptr, logn_ - 2);
				xr_ptr = xr_ptr + m4;
				xi_ptr = xi_ptr + m4;
				fft_unit(xr_ptr, xi_ptr, logn_ - 2);
				//////////////////////////////////////////////////

			}

		}

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

void DOYOUKNOW_CLASS::fft_unit6(float* xr, float* xi, int logn) {
	try {

		int logn_ = 0;
		int m = 0;
		int m2 = 0;
		int m4 = 0;
		float* xr_ptr = nullptr;
		float* xi_ptr = nullptr;

		for (int idx = logn; idx > 6; idx--) {
			for (int div1 = idx - 2; div1 > 2; div1--) {
				for (int div2 = div1 - 2; div2 > 2; div2--) {

					//////////////////////////////////////////////////
					logn_ = idx;
					m = 1 << logn_;
					m2 = 1 << (logn_ - 1);
					m4 = 1 << (logn_ - 2);
					xr_ptr = xr + m2;
					xi_ptr = xi + m2;

					logn_ = div1;
					m = 1 << logn_;
					m2 = 1 << (logn_ - 1);
					m4 = 1 << (logn_ - 2);
					xr_ptr = xr_ptr + m2;
					xi_ptr = xi_ptr + m2;

					logn_ = div2;
					m = 1 << logn_;
					m2 = 1 << (logn_ - 1);
					m4 = 1 << (logn_ - 2);

					xr_ptr = xr_ptr + m2;
					xi_ptr = xi_ptr + m2;
					fft_unit(xr_ptr, xi_ptr, logn_ - 2);
					xr_ptr = xr_ptr + m4;
					xi_ptr = xi_ptr + m4;
					fft_unit(xr_ptr, xi_ptr, logn_ - 2);
					//////////////////////////////////////////////////
					logn_ = idx;
					m = 1 << logn_;
					m2 = 1 << (logn_ - 1);
					m4 = 1 << (logn_ - 2);
					xr_ptr = xr + m2;
					xi_ptr = xi + m2;

					logn_ = div1;
					m = 1 << logn_;
					m2 = 1 << (logn_ - 1);
					m4 = 1 << (logn_ - 2);
					xr_ptr = xr_ptr + m2 + m4;
					xi_ptr = xi_ptr + m2 + m4;

					logn_ = div2;
					m = 1 << logn_;
					m2 = 1 << (logn_ - 1);
					m4 = 1 << (logn_ - 2);

					xr_ptr = xr_ptr + m2;
					xi_ptr = xi_ptr + m2;
					fft_unit(xr_ptr, xi_ptr, logn_ - 2);
					xr_ptr = xr_ptr + m4;
					xi_ptr = xi_ptr + m4;
					fft_unit(xr_ptr, xi_ptr, logn_ - 2);
					//////////////////////////////////////////////////
					logn_ = idx;
					m = 1 << logn_;
					m2 = 1 << (logn_ - 1);
					m4 = 1 << (logn_ - 2);
					xr_ptr = xr + m2 + m4;
					xi_ptr = xi + m2 + m4;

					logn_ = div1;
					m = 1 << logn_;
					m2 = 1 << (logn_ - 1);
					m4 = 1 << (logn_ - 2);
					xr_ptr = xr_ptr + m2;
					xi_ptr = xi_ptr + m2;

					logn_ = div2;
					m = 1 << logn_;
					m2 = 1 << (logn_ - 1);
					m4 = 1 << (logn_ - 2);

					xr_ptr = xr_ptr + m2;
					xi_ptr = xi_ptr + m2;
					fft_unit(xr_ptr, xi_ptr, logn_ - 2);
					xr_ptr = xr_ptr + m4;
					xi_ptr = xi_ptr + m4;
					fft_unit(xr_ptr, xi_ptr, logn_ - 2);
					//////////////////////////////////////////////////
					logn_ = idx;
					m = 1 << logn_;
					m2 = 1 << (logn_ - 1);
					m4 = 1 << (logn_ - 2);
					xr_ptr = xr + m2 + m4;
					xi_ptr = xi + m2 + m4;

					logn_ = div1;
					m = 1 << logn_;
					m2 = 1 << (logn_ - 1);
					m4 = 1 << (logn_ - 2);
					xr_ptr = xr_ptr + m2 + m4;
					xi_ptr = xi_ptr + m2 + m4;

					logn_ = div2;
					m = 1 << logn_;
					m2 = 1 << (logn_ - 1);
					m4 = 1 << (logn_ - 2);

					xr_ptr = xr_ptr + m2;
					xi_ptr = xi_ptr + m2;
					fft_unit(xr_ptr, xi_ptr, logn_ - 2);
					xr_ptr = xr_ptr + m4;
					xi_ptr = xi_ptr + m4;
					fft_unit(xr_ptr, xi_ptr, logn_ - 2);
					//////////////////////////////////////////////////

				}
			}
		}

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

void main(void) {
	try {

		DOYOUKNOW_CLASS* do_you_know_ptr;
		do_you_know_ptr = new DOYOUKNOW_CLASS();

		do_you_know_ptr->kaldi_fft();

		delete do_you_know_ptr;
		do_you_know_ptr = nullptr;

		return;

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}
}