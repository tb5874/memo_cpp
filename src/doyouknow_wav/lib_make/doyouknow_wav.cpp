#include <doyouknow_wav.hpp>

doyouknow_class::doyouknow_class(void) {
	return;
}

doyouknow_class::~doyouknow_class(void) {
	return;
}

void doyouknow_class::func_01(void) {
    try {

        printf("\n");
        printf("[ %s ]\n", ((std::string)__func__).c_str());
        printf("do you know ?\n");

        // https://www.mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/Samples.html
			// pcm format 6, channel 2, unsigned char, a-law
        std::string file_path = "C:\\Users\\k\\Desktop\\temp_wav\\M1F1-Alaw-AFsp.wav";

		wav_open(file_path);

        func_timer(1.0);

        return;

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}

void doyouknow_class::func_02(void) {
    try {

        printf("\n");
        printf("[ %s ]\n", ((std::string)__func__).c_str());
        printf("do you know ?\n");

        func_timer(1.0);

        return;

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}

void doyouknow_class::func_timer(float get_sec) {
    try {

        std::chrono::duration<float, std::milli>get_ms(get_sec * 1000.0f);
        std::chrono::steady_clock::time_point chrono_tick = std::chrono::steady_clock::now();
        while ((std::chrono::steady_clock::now() - chrono_tick) < get_ms) {
        }
        return;

        // debug code : -->
        if (false) {
            std::chrono::duration<float, std::milli>debug_ms(get_sec * 1000.0f);
            std::chrono::steady_clock::time_point debug_tick = std::chrono::steady_clock::now();
            while ((std::chrono::steady_clock::now() - debug_tick) < debug_ms) {
                printf("func_timer work : %f\n", std::chrono::duration<float>(std::chrono::steady_clock::now() - debug_tick).count());
            }
        }
        // debug code : <--
    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}

void doyouknow_class::wav_open(std::string get_path) {
    try {

        bool printf_flag = true;

        // file open        
        std::ifstream wav_fs(get_path, std::ios_base::binary);

		uint64 wav_byte = 0;
		std::string get_str = "";
		uint32 chunk_byte = 0;
		uint16 pcm_format = 0;
		uint16 wav_channel = 0;
		uint32 sample_rate = 0;
		uint32 byte_rate = 0;
		uint16 block_align = 0;
		uint16 bit_per_sample = 0;
		void* data_buf = nullptr;

		// get file byte
        wav_fs.seekg(0, std::ifstream::end);
		wav_byte = read_pos(wav_fs);

        // go to binary start position
        wav_fs.seekg(0, std::ifstream::beg);

        // [ RIFF format check ]
        get_str = read_char_n(wav_fs, 4);
        if (get_str != "RIFF") {
            throw std::runtime_error("wav file is not RIFF format");
        }

        // [ RIFF chunk byte ]
        chunk_byte = read_uint32(wav_fs);
        if (printf_flag) {
            printf("%s chunk byte : %d\n", get_str.c_str(), chunk_byte);
        }

        // [ WAVE format check ]
        get_str = read_char_n(wav_fs, 4);
        if (get_str != "WAVE") {
            throw std::runtime_error("wav file is not WAVE format");
        }

		// sub-chunk iteration
		for ( uint64 byte_pos = read_pos(wav_fs); byte_pos < wav_byte; byte_pos = read_pos(wav_fs) ) {

			// [ sub-chunk name ]
			// "char x 4"
			// If "sub-chunk name" is char 3, remain char 1 is space.
			std::string subchunk_name = read_char_n(wav_fs, 4);

			// [ sub-chunk's byte (after this 4 byte read) ]
			uint32 subchunk_byte = read_uint32(wav_fs);

			// sub-chunk byte position check
			uint64 subchunk_limit = read_pos(wav_fs) + subchunk_byte;
			if (subchunk_limit > wav_byte) {
				throw std::runtime_error("file read, overflow");
			}

			if (printf_flag) {
				printf("sub-chunk[ \"%s\" ]\n", subchunk_name.c_str());
				printf("sub-chunk[ \"%s\" ] : sub-chunk's byte (after this 4 byte read) : %d\n", subchunk_name.c_str(), subchunk_byte);
			}

			// [ sub-chunk ]
			if (subchunk_name == "fmt ") {

				// [ pcm_format ]
				// pulse code modulation
				// https://learn.microsoft.com/en-us/windows/win32/api/mmreg/ns-mmreg-waveformatex
				// https://www.mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/Samples.html
				// mmreg.h
					// 1		: WAVE_FORMAT_PCM ( need to check : sign, unsign, 8, 16, 24, 32 )
					// 3		: WAVE_FORMAT_IEEE_FLOAT ( [ float32 ] + [ -1.0 ~ 1.0 ] )
					// 6		: WAVE_FORMAT_ALAW ( alaw or ulaw, need to decode )
					// ...
					// 65534	: WAVE_FORMAT_EXTENSIBLE
				pcm_format = read_uint16(wav_fs);

				// [ wav_channel ]
					// 1 : mono
					// ...
					// N : N channel stereo
				wav_channel = read_uint16(wav_fs);

				// [ sample_rate ]
					// 1 channel information 
					// sample per 1000 ms
				sample_rate = read_uint32(wav_fs);

				// [ byte_rate ] ( = wav_channel x sample_rate x data byte size )
					// total channel information
					// byte per 1000 ms
				byte_rate = read_uint32(wav_fs);

				// [ block_align ] ( = wav_channel x data byte size )
					// total channel information
					// byte_rate / sample_rate
				block_align = read_uint16(wav_fs);

				// [ bit_per_sample ] ( = data byte size x 8 bit )
					// 1 channel information 
					// block_align / wav_channel x 8 bit
				bit_per_sample = read_uint16(wav_fs);

				if (printf_flag) {
					printf("sub-chunk[ \"%s\" ] : pcm_format : %d\n", subchunk_name.c_str(), pcm_format);
					printf("sub-chunk[ \"%s\" ] : wav_channel : %d\n", subchunk_name.c_str(), wav_channel);
					printf("sub-chunk[ \"%s\" ] : sampling_rate : %d\n", subchunk_name.c_str(), sample_rate);
					printf("sub-chunk[ \"%s\" ] : byte_rate : %d\n", subchunk_name.c_str(), byte_rate);
					printf("sub-chunk[ \"%s\" ] : block_align : %d\n", subchunk_name.c_str(), block_align);
					printf("sub-chunk[ \"%s\" ] : bit_per_sample : %d\n", subchunk_name.c_str(), bit_per_sample);
					// more "fmt " read is user option.
				}

			}
			else if (subchunk_name == "fact") {

				// [ sample length ]
					// 1 channel information 
					// sample per channel
				uint32 sample_length = read_uint32(wav_fs);

				if (printf_flag) {
					printf("sub-chunk[ \"%s\" ] : sample_length : %d\n", subchunk_name.c_str(), sample_length);
				}

			}
			else if (subchunk_name == "LIST") {

				// [ list name ]
					// normally this name is "INFO"
				std::string list_name = read_char_n(wav_fs, 4);

				for (uint64 idx = read_pos(wav_fs); idx < subchunk_limit; idx = read_pos(wav_fs)) {

					// [ list's data name ]
					std::string list_data_name = read_char_n(wav_fs, 4);

					// [ remain data's byte (after this 4 byte read) ]
					uint32 list_data_byte = read_uint32(wav_fs);

					// sub-chunk byte position check
					uint64 list_data_limit = read_pos(wav_fs) + list_data_byte;
					if (list_data_limit > subchunk_limit) {
						throw std::runtime_error("file read, overflow");
					}

					// [ list's data must be text ]
					std::string list_data_text = read_char_n(wav_fs, list_data_byte);

					// [ list's data size must be is even. if odd, add 1 byte padding ]
					if ( (list_data_byte % 2) == 1 ) {
						set_pos(wav_fs, list_data_limit + 1);
					}

					if (printf_flag) {
						printf("sub-chunk[ \"%s\" ] : [ \"%s\" ] : [ \"%s\" ]\n", subchunk_name.c_str(), list_name.c_str(), list_data_name.c_str());
						printf("sub-chunk[ \"%s\" ] : [ \"%s\" ] : [ \"%s\" ] : sub-chunk's byte (after this 4 byte read) : %d\n", subchunk_name.c_str(), list_name.c_str(), list_data_name.c_str(), list_data_byte);
						printf("sub-chunk[ \"%s\" ] : [ \"%s\" ] : [ \"%s\" ] : %s\n", subchunk_name.c_str(), list_name.c_str(), list_data_name.c_str(), list_data_text.c_str());
					}

				}

			}
			else if (subchunk_name == "data") {

				// need to know : 8, 16, 24, 32, sign, unsign, 24 bit data process ( 8 bit is zero padding )

				uint32 data_count = subchunk_byte / (bit_per_sample / 8);

				if (pcm_format == 1) {

					// int8 | uint8
					if (bit_per_sample == 8) {
						data_buf = (int8*)std::malloc(subchunk_byte);
						for (uint32 idx = 0; idx < data_count; idx++) {
							((int8*)data_buf)[idx] = read_int8(wav_fs);
						}
					}
					// int16 | uint16
					else if (bit_per_sample == 16) {
						data_buf = (int16*)std::malloc(subchunk_byte);
						for (uint32 idx = 0; idx < data_count; idx++) {
							((int16*)data_buf)[idx] = read_int16(wav_fs);
						}
					}
					else {
						// bit_per_sample == 24
							// int32 | uint32 | float32 ( 8 bit is zero padding )
						// bit_per_sample == 32
							// int32 | uint32 | float32
						throw std::runtime_error("need to update : pcm format");
					}

				}
				else if (pcm_format == 3) {

					// [ float32 ] + [ -1.0 ~ 1.0 ]
					if (bit_per_sample == 32) {
						data_buf = (float*)std::malloc(subchunk_byte);
						for (uint32 idx = 0; idx < data_count; idx++) {
							((float*)data_buf)[idx] = read_float32(wav_fs);
						}
					}
					else {
						throw std::runtime_error("need to update : pcm format");
					}

				}
				else if (pcm_format == 6) {

					// [ a-law (uint8) ]
					if (bit_per_sample == 8) {
						data_buf = (uint8*)std::malloc(subchunk_byte);
						for (uint32 idx = 0; idx < data_count; idx++) {
							((uint8*)data_buf)[idx] = read_uint8(wav_fs);
						}
					}
					else {
						throw std::runtime_error("need to update : pcm format");
					}

				}
				else if (pcm_format == 65534) {
					throw std::runtime_error("need to update : pcm format");
				}
				else {
					throw std::runtime_error("need to update : pcm format");
				}
			}
			else {

				// need to update more subchunk_name

			}

			// sub-chunk byte position check
			if ( read_pos(wav_fs) != subchunk_limit ) {

				set_pos(wav_fs, subchunk_limit);

				if (printf_flag) {
					printf("sub-chunk[ \"%s\" ] : ### need to update more read format\n", subchunk_name.c_str());
					printf("sub-chunk[ \"%s\" ] : ### go to next sub-chunk\n", subchunk_name.c_str());
				}

			}

			// sub-chunk's data size must be even. if odd, add 1 byte padding
			if ((subchunk_byte % 2) == 1) {
				set_pos(wav_fs, subchunk_limit + 1);
			}

		}

		data_buf;

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

void doyouknow_class::wav_save(std::string file_name, void* get_ptr, uint16 pcm_format, uint16 wav_channel, uint32 sample_rate, uint32 byte_rate, uint16 block_align, uint16 bit_per_sample, uint32 data_byte) {
	try {

		std::ofstream wav_fs(file_name, std::ios_base::binary);
		
		// (Byte 004) : "RIFF" : char x 4
		// (Byte 008) : "RIFF" chunk size ( "WAVE"(4) + "fmt "(24) + "data"(8) + data size ) : unsgined int
		write_char(wav_fs, (std::string)"RIFF");
		write_uint32(wav_fs, (uint32)4 + (uint32)24 + (uint32)8 + data_byte);

		// (Byte 012) : "WAVE" : char x 4
		write_char(wav_fs, (std::string)"WAVE");

		// (Byte 016) : "fmt " : char x 4
		// (Byte 020) : "fmt " chunk byte (after this byte read) : unsgined int
		// (Byte 022) : "fmt " pcm format : unsgined short
		// (Byte 024) : "fmt " wav channel : unsgined short
		// (Byte 028) : "fmt " sample rate : unsgined int
		// (Byte 032) : "fmt " byte rate : unsgined int
		// (Byte 034) : "fmt " block align : unsgined short
		// (Byte 036) : "fmt " bit per sample : unsgined short
		write_char(wav_fs, (std::string)"fmt ");
		write_uint32(wav_fs, (uint32)16);
		write_uint16(wav_fs, pcm_format);
		write_uint16(wav_fs, wav_channel);
		write_uint32(wav_fs, sample_rate);
		write_uint32(wav_fs, byte_rate);
		write_uint16(wav_fs, block_align);
		write_uint16(wav_fs, bit_per_sample);

		// (Byte 040) : "data" : char x 4
		// (Byte 044) : "data" chunk byte (after this byte read) : unsgined int
		// (Byte 045~): "data"
		write_char(wav_fs, (std::string)"data");
		write_uint32(wav_fs, data_byte);
		write_data(wav_fs, get_ptr, data_byte);

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

			//
			//
			//	// Test 01
			//	// [ save test : original ]
			//	if (true) {
			//
			//		StreamOut fout(path + "_save_original.wav");
			//
			//		// (Byte 004) : "RIFF" : char x 4
			//		// (Byte 008) : "RIFF" chunk size ( "WAVE"(4) + "fmt "(24) + "data"(8 + data size) ) : unsgined int
			//		fout.write_ascii("RIFF");
			//		fout.write_le_uint32((unsigned int)4 + (unsigned int)24 + (unsigned int)8 + subchunk_byte);
			//
			//		// (Byte 012) : "WAVE" : char x 4
			//		fout.write_ascii("WAVE");
			//
			//		// (Byte 016) : "fmt " : char x 4
			//		// (Byte 020) : "fmt " chunk byte (after this byte read) : unsgined int
			//		// (Byte 022) : "fmt " pcm format : unsgined short
			//		// (Byte 024) : "fmt " wav channel : unsgined short
			//		// (Byte 028) : "fmt " sample rate : unsgined int
			//		// (Byte 032) : "fmt " byte rate : unsgined int
			//		// (Byte 034) : "fmt " block align : unsgined short
			//		// (Byte 036) : "fmt " bit per sample : unsgined short
			//		fout.write_ascii("fmt ");
			//		fout.write_le_uint32((unsigned int)16);
			//		fout.write_le_uint16(pcm_format);
			//		fout.write_le_uint16(wav_channel);
			//		fout.write_le_uint32(sample_rate);
			//		fout.write_le_uint32(byte_rate);
			//		fout.write_le_uint16(block_align);
			//		fout.write_le_uint16(bit_per_sample);
			//
			//		// (Byte 040) : "data" : char x 4
			//		// (Byte 044) : "data" chunk byte (after this byte read) : unsgined int
			//		// (Byte 045~): "data"
			//		fout.write_ascii("data");
			//		fout.write_le_uint32(subchunk_byte); // In this if case, subchunk_byte is "data byte"
			//		fout.save_data(data_buf, subchunk_byte);
			//
			//	}
			//
			//
			//	// Test 02
			//	// [ save test : separate channel ]
			//	if (true) {
			//
			//		unsigned int ch_byte = subchunk_byte / wav_channel;
			//		unsigned int ch_sample = data_count / wav_channel;
			//
			//		// get buf
			//		void* ch_buf = nullptr;
			//		if ((pcm_format == 1) && (bit_per_sample == 8)) {
			//			ch_buf = (char*)std::malloc(ch_byte);
			//		}
			//		else if ((pcm_format == 1) && (bit_per_sample == 16)) {
			//			ch_buf = (short*)std::malloc(ch_byte);
			//		}
			//		else if ((pcm_format == 3) && (bit_per_sample == 32)) {
			//			ch_buf = (float*)std::malloc(ch_byte);
			//		}
			//		else if ((pcm_format == 6) && (bit_per_sample == 8)) {
			//			ch_buf = (unsigned char*)std::malloc(ch_byte);
			//		}
			//		else {
			//			ERROR1(DTIERR_UNKNOWN_ERROR, "need to update pcm format");
			//		}
			//
			//		// get data
			//		for (int ch = 0; ch < wav_channel; ch++) {
			//
			//			if ((pcm_format == 1) && (bit_per_sample == 8)) {
			//				for (int idx = 0; idx < ch_sample; idx++) {
			//					((char*)ch_buf)[idx] = ((char*)data_buf)[idx * wav_channel + ch];
			//				}
			//			}
			//			else if ((pcm_format == 1) && (bit_per_sample == 16)) {
			//				for (int idx = 0; idx < ch_sample; idx++) {
			//					((short*)ch_buf)[idx] = ((short*)data_buf)[idx * wav_channel + ch];
			//				}
			//			}
			//			else if ((pcm_format == 3) && (bit_per_sample == 32)) {
			//				for (int idx = 0; idx < ch_sample; idx++) {
			//					((float*)ch_buf)[idx] = ((float*)data_buf)[idx * wav_channel + ch];
			//				}
			//			}
			//			else if ((pcm_format == 6) && (bit_per_sample == 8)) {
			//				for (int idx = 0; idx < ch_sample; idx++) {
			//					((unsigned char*)ch_buf)[idx] = ((unsigned char*)data_buf)[idx * wav_channel + ch];
			//				}
			//			}
			//			else {
			//				ERROR1(DTIERR_UNKNOWN_ERROR, "need to update pcm format");
			//			}
			//
			//			StreamOut fout_ch(path + "_save_ch" + std::to_string(ch) + ".wav");
			//			fout_ch.write_ascii("RIFF");
			//			fout_ch.write_le_uint32((unsigned int)4 + (unsigned int)24 + (unsigned int)8 + ch_byte);
			//			fout_ch.write_ascii("WAVE");
			//			fout_ch.write_ascii("fmt ");
			//			fout_ch.write_le_uint32(16); // "fmt " chunk size
			//			fout_ch.write_le_uint16(pcm_format); // use original pcm_format
			//			fout_ch.write_le_uint16((unsigned short)1); // set channel 1
			//			fout_ch.write_le_uint32(sample_rate); // use original sample_rate
			//			fout_ch.write_le_uint32((unsigned int)(1 * sample_rate * bit_per_sample / 8)); // 1 channel byte rate
			//			fout_ch.write_le_uint16((unsigned short)(1 * bit_per_sample / 8)); // 1 channel block align
			//			fout_ch.write_le_uint16(bit_per_sample); // use original bit_per_sample
			//			fout_ch.write_ascii("data");
			//			fout_ch.write_le_uint32(ch_byte);
			//			fout_ch.save_data(ch_buf, ch_byte);
			//
			//		}
			//
			//		std::free(ch_buf);
			//		ch_buf = nullptr;
			//
			//	}
			//
			//
			//	// Test 03
			//	// [ save test : 1 channel -> pcm_format 3 + sample rate 16000 ]
			//	if (true) {
			//
			//		unsigned int ch_sample = data_count / wav_channel;
			//		float play_sec = (float)ch_sample / (float)sample_rate;
			//
			//		unsigned short target_pcm = 3;
			//		float target_rate = 16000.0f;
			//		int target_ch = 0;
			//
			//		unsigned int result_sample = play_sec * target_rate;
			//		unsigned int result_byte = sizeof(float) * result_sample;
			//		void* result_buf = (float*)std::malloc(result_byte);
			//		std::memset(result_buf, 0, result_byte);
			//
			//		// get buf
			//		void* ch_buf = (float*)std::malloc(sizeof(float) * ch_sample);
			//
			//		// get target channel data
			//		if ((pcm_format == 1) && (bit_per_sample == 8)) {
			//			for (int idx = 0; idx < ch_sample; idx++) {
			//				((float*)ch_buf)[idx] = ((char*)data_buf)[idx * wav_channel + target_ch];
			//			}
			//		}
			//		else if ((pcm_format == 1) && (bit_per_sample == 16)) {
			//			for (int idx = 0; idx < ch_sample; idx++) {
			//				((float*)ch_buf)[idx] = ((short*)data_buf)[idx * wav_channel + target_ch];
			//			}
			//		}
			//		else if ((pcm_format == 3) && (bit_per_sample == 32)) {
			//			for (int idx = 0; idx < ch_sample; idx++) {
			//				((float*)ch_buf)[idx] = ((float*)data_buf)[idx * wav_channel + target_ch];
			//			}
			//		}
			//		else if ((pcm_format == 6) && (bit_per_sample == 8)) {
			//			for (int idx = 0; idx < ch_sample; idx++) {
			//
			//				unsigned char alaw_data = ((unsigned char*)data_buf)[idx * wav_channel + target_ch];
			//
			//				short alaw_bias = 0x84;
			//				// 0x84 for a-law bias
			//				alaw_data ^= 0x55;
			//				// 0x55 for a-law decode rule
			//			// data: aaaa bbbb
			//			// xor : 0101 0101 (0x55)
			//			// val1: cccc dddd
			//				bool sign_flag = (alaw_data & 0x80);
			//				// 0x80 for get sign bit ( 1000 0000 )
			//			// val1: cccc dddd
			//			// and : 1000 0000
			//			// sign: @XXX XXXX
			//				short decode_short = ((alaw_data & 0xF) << 4) + 0x84;
			//				// 0xF for lower 4 bit
			//				// 0x84 for a-law bias ( 1000 0100 )
			//			// val1: cccc dddd
			//			// and : 0000 1111 (0xF)
			//			// val2: 0000 eeee << 4
			//			// val2: eeee 0000 + 1000 0100 (0x84)
			//			// val2: feee 0100
			//				decode_short <<= (alaw_data & 0x70) >> 4;
			//				// 0x70 for get upper 3 bit
			//			// val1: cccc dddd
			//			// and : 0111 0000 (0x70)
			//			// val3: 0ggg 0000 >> 4
			//			// val3: 0000 0ggg ( So, val3 is 0 ~ 7 )
			//			// val2: val2 << val3
			//				// t : every case : -->
			//				// (0) : 0000 0000 feee 0100
			//				// (1) : 0000 000f eee0 1000
			//				// (2) : 0000 00fe ee01 0000
			//				// (3) : 0000 0fee e010 0000
			//				// (4) : 0000 feee 0100 0000
			//				// (5) : 000f eee0 1000 0000
			//				// (6) : 00fe ee01 0000 0000
			//				// (7) : 0fee e010 0000 0000
			//				// t : every case : <--
			//
			//				((float*)ch_buf)[idx] = sign_flag ? (alaw_bias - decode_short) : (decode_short - alaw_bias);
			//				// sign_flag == ture : 0000 0000 1000 0100 - t
			//				// sign_flag == false: t - 0000 0000 1000 0100
			//
			//			}
			//		}
			//		else {
			//			ERROR1(DTIERR_UNKNOWN_ERROR, "need to update pcm format");
			//		}
			//
			//		if (printf_flag) {
			//			printf("\n\n");
			//			printf("ch_buf\n");
			//			for (int idx = 0; idx < ch_sample; idx++) {
			//				if (idx % 16 == 0) {
			//					printf("\n");
			//				}
			//				printf("%12.4f ", ((float*)ch_buf)[idx]);
			//			}
			//		}
			//
			//
			//		// resampling
			//		int frag_now = 0;
			//		int frag_next = 0;
			//		float frag = 0.0f;
			//		float frag_sum = 0.0f;
			//
			//		float c2r_ratio = 0.0f;
			//
			//		// up_sampling
			//		if (sample_rate < target_rate) {
			//
			//			c2r_ratio = (float)result_sample / (float)ch_sample;
			//
			//			for (int idx = 0; idx < result_sample; idx++) {
			//
			//				frag_now = idx / c2r_ratio;
			//				frag_next = (idx + 1) / c2r_ratio;
			//
			//				if (frag_now == frag_next) {
			//					((float*)result_buf)[idx] = ((float*)ch_buf)[frag_now];
			//				}
			//				else {
			//					frag = (frag_now + 1) * c2r_ratio - idx;
			//					((float*)result_buf)[idx] = ((float*)ch_buf)[frag_now] * frag;
			//					// if idx is last, do not calculate next.
			//					if (idx != (result_sample - 1)) {
			//						frag = (1.0f - frag);
			//						((float*)result_buf)[idx] += ((float*)ch_buf)[frag_next] * frag;
			//					}
			//				}
			//
			//			}
			//
			//		}
			//		// down_sampling
			//		else {
			//
			//			c2r_ratio = (float)ch_sample / (float)result_sample;
			//
			//			for (int idx = 0; idx < ch_sample; idx++) {
			//
			//				frag_now = idx / c2r_ratio;
			//				frag_next = (idx + 1) / c2r_ratio;
			//
			//				if (frag_now == frag_next) {
			//					frag = 1.0f;
			//					((float*)result_buf)[frag_now] += ((float*)ch_buf)[idx] * frag;
			//					frag_sum += 1.0f;
			//				}
			//				else {
			//					frag = (frag_now + 1) * c2r_ratio - idx;
			//					((float*)result_buf)[frag_now] += ((float*)ch_buf)[idx] * frag;
			//					frag_sum += frag;
			//					((float*)result_buf)[frag_now] /= frag_sum;
			//					// if idx is last, do not calculate next.
			//					if (idx != (ch_sample - 1)) {
			//						frag = (1.0f - frag);
			//						((float*)result_buf)[frag_next] += ((float*)ch_buf)[idx] * frag;
			//						frag_sum = frag;
			//					}
			//				}
			//
			//			}
			//		}
			//
			//		if (printf_flag) {
			//			printf("\n\n");
			//			printf("result_buf\n");
			//			for (int idx = 0; idx < result_sample; idx++) {
			//				if (idx % 16 == 0) {
			//					printf("\n");
			//				}
			//				printf("%12.4f ", ((float*)result_buf)[idx]);
			//			}
			//		}
			//
			//		// pcm format 3
			//		if ((pcm_format == 1) && (bit_per_sample == 8)) {
			//			for (int idx = 0; idx < result_sample; idx++) {
			//				((float*)result_buf)[idx] /= 128.0f;
			//			}
			//		}
			//		else if ((pcm_format == 1) && (bit_per_sample == 16)) {
			//			for (int idx = 0; idx < result_sample; idx++) {
			//				((float*)result_buf)[idx] /= 32768.0f;
			//			}
			//		}
			//		else if ((pcm_format == 3) && (bit_per_sample == 32)) {
			//			// do nothing
			//		}
			//		else if ((pcm_format == 6) && (bit_per_sample == 8)) {
			//			for (int idx = 0; idx < result_sample; idx++) {
			//				// already a-law decode (short)
			//				((float*)result_buf)[idx] /= 32768.0f;
			//			}
			//		}
			//		else {
			//			ERROR1(DTIERR_UNKNOWN_ERROR, "need to update pcm format");
			//		}
			//
			//		if (printf_flag) {
			//			printf("\n\n");
			//			printf("normalize result_buf\n");
			//			for (int idx = 0; idx < result_sample; idx++) {
			//				if (idx % 16 == 0) {
			//					printf("\n");
			//				}
			//				printf("%12.6f ", ((float*)result_buf)[idx]);
			//			}
			//		}
			//
			//		StreamOut fout_sampling(path + "_save_resampling_" + std::to_string((int)target_rate) + ".wav");
			//		fout_sampling.write_ascii("RIFF");
			//		fout_sampling.write_le_uint32((unsigned int)4 + (unsigned int)24 + (unsigned int)8 + result_byte);
			//		fout_sampling.write_ascii("WAVE");
			//		fout_sampling.write_ascii("fmt ");
			//		fout_sampling.write_le_uint32((unsigned int)16); // "fmt " chunk size
			//		fout_sampling.write_le_uint16((unsigned short)3); // pcm_format
			//		fout_sampling.write_le_uint16((unsigned short)1); // set channel 1
			//		fout_sampling.write_le_uint32((unsigned int)target_rate); // target_rate
			//		fout_sampling.write_le_uint32((unsigned int)(1 * (unsigned int)target_rate * sizeof(float))); // 1 channel byte rate
			//		fout_sampling.write_le_uint16((unsigned short)(1 * sizeof(float))); // 1 channel block align
			//		fout_sampling.write_le_uint16((unsigned short)(sizeof(float) * 8)); // bit_per_sample
			//		fout_sampling.write_ascii("data");
			//		fout_sampling.write_le_uint32(result_byte);
			//		fout_sampling.save_data(result_buf, result_byte);
			//
			//		std::free(ch_buf);
			//		ch_buf = nullptr;
			//
			//		std::free(result_buf);
			//		result_buf = nullptr;
			//
			//	}
			//
			//	device().memcpy_from_host(void_ptr(), data_buf, subchunk_byte);
			//	std::free(data_buf);
			//	data_buf = nullptr;
			//

void doyouknow_class::set_pos(std::ifstream& get_fs, uint64 get_pos) {
	try {

		get_fs.seekg(get_pos, std::ifstream::beg);

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

uint64 doyouknow_class::read_pos(std::ifstream& get_fs) {

	uint64 get_pos = 0;

	try {

		get_pos = (get_fs.tellg() == -1) ? throw std::runtime_error("file stream position is -1") : get_fs.tellg();

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return get_pos;

}

std::string doyouknow_class::read_char_n(std::ifstream& get_fs, uint64 get_n) {
    
    std::string get_str = "";

    try {

		int8 get_char = 0;

        for (uint64 idx = 0; idx < get_n; idx++) {
            get_fs.read(&get_char, 1);
            get_str += get_char;
        }

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return get_str;

}

uint8 doyouknow_class::read_uint8(std::ifstream& get_fs) {

	uint8 get_uint8 = 0;

    try{

		int8 bytes = 0;
        get_fs.read(&bytes, 1);

        get_uint8 = bytes;

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return get_uint8;

}

uint16 doyouknow_class::read_uint16(std::ifstream& get_fs) {

	uint16 get_uint16 = 0;

    try {

		int8 bytes[2] = { 0, };
        get_fs.read(bytes, 2);

        ((int8*)&get_uint16)[0] = bytes[0];
        ((int8*)&get_uint16)[1] = bytes[1];

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return get_uint16;

}

uint32 doyouknow_class::read_uint32(std::ifstream& get_fs) {

	uint32 get_uint32 = 0;

    try {

		int8 bytes[4] = { 0, };
        get_fs.read(bytes, 4);

        ((int8*)&get_uint32)[0] = bytes[0];
        ((int8*)&get_uint32)[1] = bytes[1];
        ((int8*)&get_uint32)[2] = bytes[2];
        ((int8*)&get_uint32)[3] = bytes[3];

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return get_uint32;

}

int8 doyouknow_class::read_int8(std::ifstream& get_fs) {

	int8 get_int8 = 0;

	try {

		int8 bytes = 0;
		get_fs.read(&bytes, 1);

		get_int8 = bytes;

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return get_int8;

}

int16 doyouknow_class::read_int16(std::ifstream& get_fs) {

	int16 get_int16 = 0;

	try {

		int8 bytes[2] = { 0, };
		get_fs.read(bytes, 2);

		((int8*)&get_int16)[0] = bytes[0];
		((int8*)&get_int16)[1] = bytes[1];

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return get_int16;

}

int32 doyouknow_class::read_int32(std::ifstream& get_fs) {

	int32 get_int32 = 0;

	try {

		int8 bytes[4] = { 0, };
		get_fs.read(bytes, 4);

		((int8*)&get_int32)[0] = bytes[0];
		((int8*)&get_int32)[1] = bytes[1];
		((int8*)&get_int32)[2] = bytes[2];
		((int8*)&get_int32)[3] = bytes[3];

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return get_int32;

}

float doyouknow_class::read_float32(std::ifstream& get_fs) {

	float get_float32 = 0.0f;

	try {

		int8 bytes[4] = { 0, };
		get_fs.read(bytes, 4);

		((int8*)&get_float32)[0] = bytes[0];
		((int8*)&get_float32)[1] = bytes[1];
		((int8*)&get_float32)[2] = bytes[2];
		((int8*)&get_float32)[3] = bytes[3];

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return get_float32;

}


void write_char(std::ofstream& get_fs, std::string get_data) {
	try {

		int8 get_char = 0;

		for (uint64 idx = 0; idx < get_data.size(); idx++){
			get_char = get_data.at(idx);
			get_fs.write(&get_char, 1);
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

void doyouknow_class::write_uint8(std::ofstream& get_fs, uint8 get_data) {
	try {

		int8 bytes = 0;
		bytes = get_data;
		get_fs.write(&bytes, 1);

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

void doyouknow_class::write_uint16(std::ofstream& get_fs, uint16 get_data) {
	try {

		int8 bytes[2] = { 0, };
		bytes[0] = ((int8*)&get_data)[0];
		bytes[1] = ((int8*)&get_data)[1];
		get_fs.write(bytes, 2);

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

void doyouknow_class::write_uint32(std::ofstream& get_fs, uint32 get_data) {
	try {

		int8 bytes[4] = { 0, };
		bytes[0] = ((int8*)&get_data)[0];
		bytes[1] = ((int8*)&get_data)[1];
		bytes[2] = ((int8*)&get_data)[2];
		bytes[3] = ((int8*)&get_data)[3];
		get_fs.write(bytes, 4);

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

void doyouknow_class::write_data(std::ofstream& get_fs, void* get_ptr, uint32 get_data) {
	try {

		int8 bytes = 0;
		get_fs.write(&bytes, 1);

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}