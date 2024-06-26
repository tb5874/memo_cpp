#include <doyouknow_kaldi.hpp>

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

        // code write : -->

        // Dataset : https://www.openslr.org/resources.php
            // waves_yesno.tar.gz
            // 0_0_0_0_1_1_1_1.wav
            // 0 is no
            // 1 is yes
                // no no no no no yes yes yes yes yse

        // sox --i 0_0_0_0_1_1_1_1.wav
            // Input File : '0_0_0_0_1_1_1_1.wav'
            //     Channels : 1
            //     Sample Rate : 8000
            //     Precision : 16 - bit
            //     Duration : 00 : 00 : 06.35 = 50800 samples ~476.25 CDDA sectors
            //     File Size : 102k
            //     Bit Rate : 128k
            //     Sample Encoding : 16 - bit Signed Integer PCM

        // sudo ffmpeg -i 0_0_0_0_1_1_1_1.wav -ar 16000 -c:a pcm_f32le yesno_16000.wav

        // sox --i yesno_16000.wav
            // Input File : 'yesno_16000.wav'
            //     Channels : 1
            //     Sample Rate : 16000
            //     Precision : 25 - bit
            //     Duration : 00 : 00 : 06.35 = 101600 samples ~476.25 CDDA sectors
            //     File Size : 407k
            //     Bit Rate : 512k
            //     Sample Encoding : 32 - bit Floating Point PCM


        int get_int32 = 0;
        float get_fp32 = 0.0f;
        int get_byte_count = 0;
        int get_data_count = 0;
        std::vector<float> vfp32_yesno;
        vfp32_yesno.clear();

        // file open
        std::ifstream fs_yesno("/home/user/yesno_16000.wav", std::ios_base::binary);

        // index 0 ~ 105              : ...
        // index 106 ~ 109 ( 4 byte ) : "data"
        // index 110 ~ 399            : ...
        fs_yesno.seekg(0, std::ios_base::beg);
        read_char8(fs_yesno, 400);

        // index 110 ~ 113 ( 4 byte ) : "406400"
        fs_yesno.seekg(110, std::ios_base::beg);
        read_int32(fs_yesno);       

        // set end position of file stream
        fs_yesno.seekg(0, fs_yesno.end);
        // get total byte count
        get_byte_count = fs_yesno.tellg();
        // get data count
        get_data_count = (get_byte_count - 114) / 4;

        // get data
        fs_yesno.seekg(114, std::ios_base::beg);
        for (int idx = 0; idx < get_data_count; idx++) {
            get_fp32 = read_fp32(fs_yesno);
            get_fp32 = get_fp32 * (1 << 15); // get_fp32 * 32768
            vfp32_yesno.push_back(get_fp32);
        }

        if (true) {
            for (int idx = 0; idx < vfp32_yesno.size(); idx++) {
                if (idx == 16) {
                    printf("\n");
                }
                printf("%12.6f ", vfp32_yesno.at(idx));
            }
        }

        fs_yesno.close();
        
        // code write : <--

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

char doyouknow_class::read_char8(std::istream& get_fs, int get_count) {
    char bytes;
    get_fs.read(&bytes, 1);

    return;

}

int doyouknow_class::read_int32(std::istream& get_fs) {
    char bytes[4];
    get_fs.read(bytes, 4);

    int get_value = 0;
    ((char*)&get_value)[0] = bytes[0];
    ((char*)&get_value)[1] = bytes[1];
    ((char*)&get_value)[2] = bytes[2];
    ((char*)&get_value)[3] = bytes[3];

    if (true) {
        printf("read_int32() int : %d\n", get_value);
    }

    return get_value;
}


float doyouknow_class::read_fp32(std::istream& get_fs) {
    char bytes[4];
    get_fs.read(bytes, 4);

    float get_value = 0.0f;
    ((char*)&get_value)[0] = bytes[0];
    ((char*)&get_value)[1] = bytes[1];
    ((char*)&get_value)[2] = bytes[2];
    ((char*)&get_value)[3] = bytes[3];

    if (false) {
        printf("read_f32() float : %f\n", get_value);
    }

    return get_value;
}
