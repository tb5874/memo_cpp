#pragma once

// short int == short == 16
// long int == long == 32
// long long int == long long == 64

#include <string>
#include <exception>
#include <chrono>
#include <iostream>
#include <fstream>
#include <map>

typedef char int8;
typedef short int int16;
typedef long int int32;
typedef long long int int64;

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned long int uint32;
typedef unsigned long long int uint64;


class str_uint64 {

	public:
		str_uint64(void) {};
		~str_uint64(void) {
			_item.clear();
		};

	private:
		std::map<std::string, uint64> _item;

	public:
		uint64& operator[](const char* key){			
			//std::string get_key = std::string(key);
			if (_item.find(key) == _item.end()) {
				throw std::runtime_error("key is empty, use function : add(\"key\", value)\n");
			}
			return _item[std::string(key)];
		}

		void add(const char* key, uint64 value) {
			_item[(std::string)(key)] = value;
			return;
		}

		void show(void) {
			std::map<std::string, uint64>::iterator itr = _item.begin();
			printf("\n");
			for (uint64 idx = 0; idx < _item.size(); idx++) {
				printf("%s : %d\n", itr->first.c_str(), itr->second);
				if (idx == _item.size() - 1) {
					break;
				}
				else {					
					itr++;
				}
			}
			printf("\n");
			return;
		}

		void clear(void) {
			_item.clear();
			return;
		}

};

class doyouknow_class{

	public:
		doyouknow_class(void);
		~doyouknow_class(void);

	public:
		void func_01(void);
		void func_02(void);
		void func_timer(float get_sec);
		
	public:
		void wav_open(std::string& get_path);
		void wav_save(std::string& file_name, void* get_buf, str_uint64& get_args);

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
		void write_char(std::ofstream& get_fs, const char* get_char);
		void write_uint8(std::ofstream& get_fs, uint8 get_data);
		void write_uint16(std::ofstream& get_fs, uint16 get_data);
		void write_uint32(std::ofstream& get_fs, uint32 get_data);
		void write_int8(std::ofstream& get_fs, int8 get_data);
		void write_int16(std::ofstream& get_fs, int16 get_data);
		void write_int32(std::ofstream& get_fs, int32 get_data);
		void write_float32(std::ofstream& get_fs, float get_data);
		void write_data(std::ofstream& get_fs, void* get_buf, uint32 get_data_byte);

};
