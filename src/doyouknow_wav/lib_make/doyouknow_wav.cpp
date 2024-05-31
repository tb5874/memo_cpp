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

		std::string file_path = "C:\\Users\\k\\Desktop\\temp_wav\\M1F1-Alaw-AFsp.wav";
			// https://www.mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/Samples.html
			// pcm format 6, channel 2, unsigned char, a-law

		// save test : wav open and save
		void* wav_buf = nullptr;
		str_uint64 wav_args;
		wav_open(file_path, wav_buf, wav_args);
		wav_save(file_path + "_original.wav", wav_buf, wav_args);
		std::free(wav_buf);
		wav_buf = nullptr;


		// save test : seperate channel save
		uint16 ch_target = 0;
		void* ch_buf = nullptr;
		str_uint64 ch_args;
		wav_open(file_path, wav_buf, wav_args);
		wav_ch(wav_buf, wav_args, ch_target, ch_buf, ch_args);
		wav_save(file_path + "_ch" + std::to_string(ch_target) + ".wav", ch_buf, ch_args);
		std::free(wav_buf);
		std::free(ch_buf);
		wav_buf = nullptr;
		ch_buf = nullptr;


		// save test : resampling save
		float re_target = 32000.0f;
		void* re_buf = nullptr;
		str_uint64 re_args;
		wav_open(file_path, wav_buf, wav_args);
		wav_re(wav_buf, wav_args, re_target, re_buf, re_args);
		wav_save(file_path + "_resampling" + std::to_string((uint32)re_target) + ".wav", re_buf, re_args);
		std::free(wav_buf);
		std::free(re_buf);
		wav_buf = nullptr;
		re_buf = nullptr;


		// just sleep ... 
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

void doyouknow_class::wav_open(std::string& get_path, void*& wav_buf, str_uint64& wav_args) {
    try {

		if (wav_buf != nullptr) {
			std::free(wav_buf);
		}

		wav_args.clear();

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
		uint32 data_byte = 0;
		uint32 data_count = 0;

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
            printf("chunk[ \"%s\" ] chunk's byte (after this 4 byte read) : %d\n", get_str.c_str(), chunk_byte);
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

				data_byte = subchunk_byte;
				
				data_count = data_byte / (bit_per_sample / 8);

				if (pcm_format == 1) {

					// int8 | uint8
					if (bit_per_sample == 8) {
						wav_buf = (int8*)std::malloc(data_byte);
						for (uint32 idx = 0; idx < data_count; idx++) {
							((int8*)wav_buf)[idx] = read_int8(wav_fs);
						}
					}
					// int16 | uint16
					else if (bit_per_sample == 16) {
						wav_buf = (int16*)std::malloc(data_byte);
						for (uint32 idx = 0; idx < data_count; idx++) {
							((int16*)wav_buf)[idx] = read_int16(wav_fs);
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

					// [ float32, -1.0 ~ 1.0 ]
					if (bit_per_sample == 32) {
						wav_buf = (float*)std::malloc(data_byte);
						for (uint32 idx = 0; idx < data_count; idx++) {
							((float*)wav_buf)[idx] = read_float32(wav_fs);
						}
					}
					else {
						throw std::runtime_error("need to update : pcm format");
					}

				}
				else if (pcm_format == 6) {

					// [ a-law (uint8) ]
					if (bit_per_sample == 8) {
						wav_buf = (uint8*)std::malloc(data_byte);
						for (uint32 idx = 0; idx < data_count; idx++) {
							((uint8*)wav_buf)[idx] = read_uint8(wav_fs);
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

		wav_args.add("pcm_format", pcm_format);
		wav_args.add("wav_channel", wav_channel);
		wav_args.add("sample_rate", sample_rate);
		wav_args.add("byte_rate", byte_rate);
		wav_args.add("block_align", block_align);
		wav_args.add("bit_per_sample", bit_per_sample);
		wav_args.add("data_byte", data_byte);
		wav_args.show();

		wav_fs.close();

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

void doyouknow_class::wav_save(std::string& file_name, void*& get_buf, str_uint64& get_args) {
	try {

		uint16 pcm_format = get_args["pcm_format"];
		uint16 wav_channel = get_args["wav_channel"];
		uint32 sample_rate = get_args["sample_rate"];
		uint32 byte_rate = get_args["byte_rate"];
		uint16 block_align = get_args["block_align"];
		uint16 bit_per_sample = get_args["bit_per_sample"];
		uint32 data_byte = get_args["data_byte"];

		std::ofstream wav_fs(file_name, std::ios_base::binary);
		
		// (Byte 004) : "RIFF" : char x 4
		// (Byte 008) : "RIFF" chunk byte (after this 4 byte read) : unsgined int
			// "WAVE"(4) + "fmt "(24) + "data"(8) + data_byte )
		write_char(wav_fs, "RIFF");
		write_uint32(wav_fs, (uint32)4 + (uint32)24 + (uint32)8 + data_byte);

		// (Byte 012) : "WAVE" : char x 4
		write_char(wav_fs, "WAVE");

		// (Byte 016) : "fmt " : char x 4
		// (Byte 020) : "fmt " chunk byte (after this 4 byte read) : unsgined int
		// (Byte 022) : "fmt " pcm format : unsgined short
		// (Byte 024) : "fmt " wav channel : unsgined short
		// (Byte 028) : "fmt " sample rate : unsgined int
		// (Byte 032) : "fmt " byte rate : unsgined int
		// (Byte 034) : "fmt " block align : unsgined short
		// (Byte 036) : "fmt " bit per sample : unsgined short
		write_char(wav_fs, "fmt ");
		write_uint32(wav_fs, (uint32)16);
		write_uint16(wav_fs, pcm_format);
		write_uint16(wav_fs, wav_channel);
		write_uint32(wav_fs, sample_rate);
		write_uint32(wav_fs, byte_rate);
		write_uint16(wav_fs, block_align);
		write_uint16(wav_fs, bit_per_sample);

		// (Byte 040) : "data" : char x 4
		// (Byte 044) : "data" chunk byte (after this 4 byte read) : unsgined int
		// (Byte 045~): "data"
		write_char(wav_fs, "data");
		write_uint32(wav_fs, data_byte);
		write_data(wav_fs, get_buf, data_byte);

		wav_fs.close();

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

void doyouknow_class::wav_ch(void*& get_buf, str_uint64& get_args, uint16 ch_target, void*& ch_buf, str_uint64& ch_args) {
	try {

		if (ch_buf != nullptr) {
			std::free(ch_buf);
		}

		ch_args.clear();

		uint16 pcm_format = get_args["pcm_format"];
		uint16 wav_channel = get_args["wav_channel"];
		uint32 sample_rate = get_args["sample_rate"];
		uint32 byte_rate = get_args["byte_rate"];
		uint16 block_align = get_args["block_align"];
		uint16 bit_per_sample = get_args["bit_per_sample"];
		uint32 data_byte = get_args["data_byte"];
		uint32 ch_byte = data_byte / wav_channel;
		uint32 ch_count = data_byte / wav_channel / (bit_per_sample / 8);

		if ((pcm_format == 1) && (bit_per_sample == 8)) {
			ch_buf = (int8*)std::malloc(ch_byte);
		}
		else if ((pcm_format == 1) && (bit_per_sample == 16)) {
			ch_buf = (int16*)std::malloc(ch_byte);
		}
		else if ((pcm_format == 3) && (bit_per_sample == 32)) {
			ch_buf = (float*)std::malloc(ch_byte);
		}
		else if ((pcm_format == 6) && (bit_per_sample == 8)) {
			ch_buf = (uint8*)std::malloc(ch_byte);
		}
		else {
			throw std::runtime_error("need to update : pcm format");
		}

		if ((pcm_format == 1) && (bit_per_sample == 8)) {
			for (uint32 idx = 0; idx < ch_count; idx++) {
				((int8*)ch_buf)[idx] = ((int8*)get_buf)[idx * wav_channel + ch_target];
			}
		}
		else if ((pcm_format == 1) && (bit_per_sample == 16)) {
			for (uint32 idx = 0; idx < ch_count; idx++) {
				((int16*)ch_buf)[idx] = ((int16*)get_buf)[idx * wav_channel + ch_target];
			}
		}
		else if ((pcm_format == 3) && (bit_per_sample == 32)) {
			for (uint32 idx = 0; idx < ch_count; idx++) {
				((float*)ch_buf)[idx] = ((float*)get_buf)[idx * wav_channel + ch_target];
			}
		}
		else if ((pcm_format == 6) && (bit_per_sample == 8)) {
			for (uint32 idx = 0; idx < ch_count; idx++) {
				((uint8*)ch_buf)[idx] = ((uint8*)get_buf)[idx * wav_channel + ch_target];
			}
		}
		else {
			throw std::runtime_error("need to update : pcm format");
		}

		ch_args.add("pcm_format", pcm_format);
		ch_args.add("wav_channel", 1);
		ch_args.add("sample_rate", sample_rate);
		ch_args.add("byte_rate", 1 * sample_rate * (bit_per_sample / 8));
		ch_args.add("block_align", 1 * (bit_per_sample / 8));
		ch_args.add("bit_per_sample", bit_per_sample);
		ch_args.add("data_byte", ch_byte);
		ch_args.show();

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

void doyouknow_class::wav_re(void*& get_buf, str_uint64& get_args, float re_target, void*& re_buf, str_uint64& re_args) {
	try {

		if (re_buf != nullptr) {
			std::free(re_buf);
		}

		re_args.clear();

		uint16 pcm_format = get_args["pcm_format"];
		uint16 wav_channel = get_args["wav_channel"];
		uint32 sample_rate = get_args["sample_rate"];
		uint32 byte_rate = get_args["byte_rate"];
		uint16 block_align = get_args["block_align"];
		uint16 bit_per_sample = get_args["bit_per_sample"];
		uint32 data_byte = get_args["data_byte"];
		uint32 data_count = data_byte / (bit_per_sample / 8);

		// type to float32
		float* float_buf = (float*)std::malloc(sizeof(float) * data_count);
		if ((pcm_format == 1) && (bit_per_sample == 8)) {
			for (uint32 idx = 0; idx < data_count; idx++) {
				float_buf[idx] = (float)((int8*)get_buf)[idx];
			}
		}
		else if ((pcm_format == 1) && (bit_per_sample == 16)) {
			for (uint32 idx = 0; idx < data_count; idx++) {
				float_buf[idx] = (float)((int16*)get_buf)[idx];
			}
		}
		else if ((pcm_format == 3) && (bit_per_sample == 32)) {
			for (uint32 idx = 0; idx < data_count; idx++) {
				float_buf[idx] = ((float*)get_buf)[idx];
			}
		}
		else if ((pcm_format == 6) && (bit_per_sample == 8)) {
			for (uint32 idx = 0; idx < data_count; idx++) {
				float_buf[idx] = (float)((uint8*)get_buf)[idx];
			}
		}
		else {
			throw std::runtime_error("need to update : pcm format");
		}

		// resampling 
		uint32 ch_count = data_count / wav_channel;
		float* ch_buf = (float*)std::malloc(sizeof(float) * ch_count);

		float play_sec = (float)ch_count / (float)sample_rate;
		float target_rate = re_target;
		uint32 result_count = play_sec * target_rate;
		float* temp_buf = (float*)std::malloc(sizeof(float) * result_count);

		uint32 result_byte = result_count * (bit_per_sample / 8) * wav_channel;
		if ((pcm_format == 1) && (bit_per_sample == 8)) {
			re_buf = (int8*)std::malloc(result_byte);
		}
		else if ((pcm_format == 1) && (bit_per_sample == 16)) {
			re_buf = (int16*)std::malloc(result_byte);
		}
		else if ((pcm_format == 3) && (bit_per_sample == 32)) {
			re_buf = (float*)std::malloc(result_byte);
		}
		else if ((pcm_format == 6) && (bit_per_sample == 8)) {
			re_buf = (uint8*)std::malloc(result_byte);
		}
		else {
			throw std::runtime_error("need to update : pcm format");
		}

		for (uint16 ch = 0; ch < wav_channel; ch++) {

			// original to channel
			for (uint32 idx = 0; idx < ch_count; idx++) {
				ch_buf[idx] = float_buf[idx * wav_channel + ch];
			}

			float w2r_ratio = 0.0f;
			int frag_now = 0;
			int frag_next = 0;
			float frag = 0.0f;
			float frag_sum = 0.0f;
			
			if (sample_rate < target_rate) {
				// channel - up sampling
				w2r_ratio = (float)result_count / (float)ch_count;
				for (int idx = 0; idx < result_count; idx++) {
					frag_now = idx / w2r_ratio;
					frag_next = (idx + 1) / w2r_ratio;
					if (frag_now == frag_next) {
						frag = 1.0f;
						temp_buf[idx] = ch_buf[frag_now] * frag;
					}
					else {
						frag = (frag_now + 1) * w2r_ratio - idx;
						temp_buf[idx] = ch_buf[frag_now] * frag;

						// if idx is last, do not calculate next.
						if (idx != (result_count - 1)) {
							frag = (1.0f - frag);
							temp_buf[idx] += ch_buf[frag_next] * frag;
						}
					}
				}
			}
			else {
				// channel - down sampling
				w2r_ratio = (float)ch_count / (float)result_count;
				for (int idx = 0; idx < ch_count; idx++) {
					frag_now = idx / w2r_ratio;
					frag_next = (idx + 1) / w2r_ratio;
					if (frag_now == frag_next) {
						frag = 1.0f;
						temp_buf[frag_now] += ch_buf[idx] * frag;
						frag_sum += frag;
					}
					else {
						frag = (frag_now + 1) * w2r_ratio - idx;
						temp_buf[frag_now] += ch_buf[idx] * frag;
						frag_sum += frag;
						temp_buf[frag_now] /= frag_sum;

						// if idx is last, do not calculate next.
						if (idx != (ch_count - 1)) {
							frag = (1.0f - frag);
							temp_buf[frag_next] += ch_buf[idx] * frag;
							frag_sum = frag;
						}
					}
				}
			}

			// channel to original
			if ((pcm_format == 1) && (bit_per_sample == 8)) {
				for (uint32 idx = 0; idx < result_count; idx++) {
					((int8*)re_buf)[idx * wav_channel + ch] = (int8)(temp_buf[idx]);
				}
			}
			else if ((pcm_format == 1) && (bit_per_sample == 16)) {
				for (uint32 idx = 0; idx < result_count; idx++) {
					((int16*)re_buf)[idx * wav_channel + ch] = (int16)(temp_buf[idx]);
				}
			}
			else if ((pcm_format == 3) && (bit_per_sample == 32)) {
				for (uint32 idx = 0; idx < result_count; idx++) {
					((float*)re_buf)[idx * wav_channel + ch] = (float)(temp_buf[idx]);
				}
			}
			else if ((pcm_format == 6) && (bit_per_sample == 8)) {
				for (uint32 idx = 0; idx < result_count; idx++) {
					((uint8*)re_buf)[idx * wav_channel + ch] = (uint8)(temp_buf[idx]);
				}
			}
			else {
				throw std::runtime_error("need to update : pcm format");
			}

		}

		re_args.add("pcm_format", pcm_format);
		re_args.add("wav_channel", wav_channel);
		re_args.add("sample_rate", target_rate);
		re_args.add("byte_rate", wav_channel * target_rate * (bit_per_sample / 8));
		re_args.add("block_align", wav_channel * (bit_per_sample / 8));
		re_args.add("bit_per_sample", bit_per_sample);
		re_args.add("data_byte", result_byte);
		re_args.show();

		std::free(float_buf);
		float_buf = nullptr;

		std::free(ch_buf);
		ch_buf = nullptr;

		std::free(temp_buf);
		temp_buf = nullptr;

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

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
		int8 get_byte = 0;
        get_fs.read(&get_byte, 1);
        get_uint8 = get_byte;
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
		int8 get_byte[2] = { 0, };
        get_fs.read(get_byte, 2);
        ((int8*)&get_uint16)[0] = get_byte[0];
        ((int8*)&get_uint16)[1] = get_byte[1];
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
		int8 get_byte[4] = { 0, };
        get_fs.read(get_byte, 4);
        ((int8*)&get_uint32)[0] = get_byte[0];
        ((int8*)&get_uint32)[1] = get_byte[1];
        ((int8*)&get_uint32)[2] = get_byte[2];
        ((int8*)&get_uint32)[3] = get_byte[3];
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
		int8 get_byte = 0;
		get_fs.read(&get_byte, 1);
		get_int8 = get_byte;
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
		int8 get_byte[2] = { 0, };
		get_fs.read(get_byte, 2);
		((int8*)&get_int16)[0] = get_byte[0];
		((int8*)&get_int16)[1] = get_byte[1];
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
		int8 get_byte[4] = { 0, };
		get_fs.read(get_byte, 4);
		((int8*)&get_int32)[0] = get_byte[0];
		((int8*)&get_int32)[1] = get_byte[1];
		((int8*)&get_int32)[2] = get_byte[2];
		((int8*)&get_int32)[3] = get_byte[3];
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
		int8 get_byte[4] = { 0, };
		get_fs.read(get_byte, 4);
		((int8*)&get_float32)[0] = get_byte[0];
		((int8*)&get_float32)[1] = get_byte[1];
		((int8*)&get_float32)[2] = get_byte[2];
		((int8*)&get_float32)[3] = get_byte[3];
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}
	return get_float32;
}

void doyouknow_class::write_char(std::ofstream& get_fs, const char* get_char) {
	try {
		std::string get_str(get_char);
		int8 get_char = 0;
		for (uint64 idx = 0; idx < get_str.size(); idx++){
			get_char = get_str.at(idx);
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
		int8 get_byte = 0;
		get_byte = get_data;
		get_fs.write(&get_byte, 1);
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
		int8 get_byte[2] = { 0, };
		get_byte[0] = ((int8*)&get_data)[0];
		get_byte[1] = ((int8*)&get_data)[1];
		get_fs.write(get_byte, 2);
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
		int8 get_byte[4] = { 0, };
		get_byte[0] = ((int8*)&get_data)[0];
		get_byte[1] = ((int8*)&get_data)[1];
		get_byte[2] = ((int8*)&get_data)[2];
		get_byte[3] = ((int8*)&get_data)[3];
		get_fs.write(get_byte, 4);
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}
	return;
}

void doyouknow_class::write_int8(std::ofstream& get_fs, int8 get_data) {
	try {
		int8 get_byte = 0;
		get_byte = get_data;
		get_fs.write(&get_byte, 1);
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}
	return;
}

void doyouknow_class::write_int16(std::ofstream& get_fs, int16 get_data) {
	try {
		int8 get_byte[2] = { 0, };
		get_byte[0] = ((int8*)&get_data)[0];
		get_byte[1] = ((int8*)&get_data)[1];
		get_fs.write(get_byte, 2);
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}
	return;
}

void doyouknow_class::write_int32(std::ofstream& get_fs, int32 get_data) {
	try {
		int8 get_byte[4] = { 0, };
		get_byte[0] = ((int8*)&get_data)[0];
		get_byte[1] = ((int8*)&get_data)[1];
		get_byte[2] = ((int8*)&get_data)[2];
		get_byte[3] = ((int8*)&get_data)[3];
		get_fs.write(get_byte, 4);
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}
	return;
}

void doyouknow_class::write_float32(std::ofstream& get_fs, float get_data) {
	try {
		int8 get_byte[4] = { 0, };
		get_byte[0] = ((int8*)&get_data)[0];
		get_byte[1] = ((int8*)&get_data)[1];
		get_byte[2] = ((int8*)&get_data)[2];
		get_byte[3] = ((int8*)&get_data)[3];
		get_fs.write(get_byte, 4);
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}
	return;
}

void doyouknow_class::write_data(std::ofstream& get_fs, void*& get_buf, uint32 get_data_byte) {
	try {
		int8 get_byte = 0;
		for (uint32 idx = 0; idx < get_data_byte; idx++) {
			get_byte = ((int8*)get_buf)[idx];
			get_fs.write(&get_byte, 1);
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
