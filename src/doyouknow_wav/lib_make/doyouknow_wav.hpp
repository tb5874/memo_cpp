#pragma once

// short int == short == 16
// long int == long == 32
// long long int == long long == 64

typedef char int8;
typedef short int int16;
typedef long int int32;
typedef long long int int64;

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned long int uint32;
typedef unsigned long long int uint64;

#include <string>
#include <exception>
#include <chrono>
#include <iostream>
#include <fstream>

class doyouknow_class{

	public:
		doyouknow_class(void);
		~doyouknow_class(void);

	public:
		void func_01(void);
		void func_02(void);
		void func_timer(float get_sec);
		
	public:
		void wav_open(std::string get_path);
		void wav_save(std::string file_name, void* get_ptr, uint16 pcm_format, uint16 wav_channel, uint32 sample_rate, uint32 byte_rate, uint16 block_align, uint16 bit_per_sample, uint32 data_byte);

	public:
		uint64 read_pos(std::ifstream& get_fs);
		void set_pos(std::ifstream& get_fs, uint64 get_pos);

	public:
		std::string read_char_n(std::ifstream& get_fs, uint64 get_n);
		uint8 read_uint8(std::ifstream& get_fs);
		uint16 read_uint16(std::ifstream& get_fs);
		uint32 read_uint32(std::ifstream& get_fs);
		int8 read_int8(std::ifstream& get_fs);
		int16 read_int16(std::ifstream& get_fs);
		int32 read_int32(std::ifstream& get_fs);
		float read_float32(std::ifstream& get_fs);
		
	public:
		void write_char(std::ofstream& get_fs, std::string get_data);
		void write_uint8(std::ofstream& get_fs, uint8 get_data);
		void write_uint16(std::ofstream& get_fs, uint16 get_data);
		void write_uint32(std::ofstream& get_fs, uint32 get_data);
		void write_int8(std::ofstream& get_fs, int8 get_data);
		void write_int16(std::ofstream& get_fs, int16 get_data);
		void write_int32(std::ofstream& get_fs, int32 get_data);
		void write_float32(std::ofstream& get_fs);
		void write_data(std::ofstream& get_fs, void* get_ptr, uint32 get_data);

};
